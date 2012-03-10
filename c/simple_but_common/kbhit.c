#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


static struct termios       save_termios;
static int                  ttysavefd = -1;
static enum { RESET, RAW, CBREAK } ttystate = RESET;

int
tty_cbreak(int fd) /* put terminal into a cbreak mode */
{
  int              err;
  struct termios   buf;

  if (ttystate != RESET) {
    errno = EINVAL;
    return(-1);
  }
  if (tcgetattr(fd, &buf) < 0)
    return(-1);
  save_termios = buf; /* structure copy */

  /*
   * Echo off, canonical mode off.
   */
  buf.c_lflag &= ~(ECHO | ICANON);

  /*
   * Case B: 1 byte at a time, no timer.
   */
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;
  if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
    return(-1);

  /*
   * Verify that the changes stuck. tcsetattr can return 0 on
   * partial success.
   */
  if (tcgetattr(fd, &buf) < 0) {
    err = errno;
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = err;
    return(-1);
  }
  if ((buf.c_lflag & (ECHO | ICANON)) || buf.c_cc[VMIN] != 1 ||
      buf.c_cc[VTIME] != 0) {
    /*
     * Only some of the changes were made. Restore the
     * original settings.
     */
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = EINVAL;
    return(-1);
  }

  ttystate = CBREAK;
  ttysavefd = fd;
  return(0);
}

int
tty_raw(int fd)     /* put terminal into a raw mode */
{
  int             err;
  struct termios  buf;

  if (ttystate != RESET) {
    errno = EINVAL;
    return(-1);
  }
  if (tcgetattr(fd, &buf) < 0)
    return(-1);
  save_termios = buf; /* structure copy */

  /*
   * Echo off, canonical mode off, extended input
   * processing off, signal chars off.
   */
  buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  /*
   * No SIGINT on BREAK, CR-to-NL off, input parity
   * check off, don't strip 8th bit on input, output
   * flow control off.
   */
  buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

  /*
   * Clear size bits, parity checking off.
   */
  buf.c_cflag &= ~(CSIZE | PARENB);

  /*
   * Set 8 bits/char.
   */
  buf.c_cflag |= CS8;

  /*
   * Output processing off.
   */
  buf.c_oflag &= ~(OPOST);

  /*
   * Case B: 1 byte at a time, no timer.
   */
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;
  if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
    return(-1);

  /*
   * Verify that the changes stuck. tcsetattr can return 0 on
   * partial success.
   */
  if (tcgetattr(fd, &buf) < 0) {
    err = errno;
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = err;
    return(-1);
  }
  if ((buf.c_lflag & (ECHO | ICANON | IEXTEN | ISIG)) ||
      (buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON)) ||
      (buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 ||
      (buf.c_oflag & OPOST) || buf.c_cc[VMIN] != 1 ||
      buf.c_cc[VTIME] != 0) {
    /*
     * Only some of the changes were made. Restore the
     * original settings.
     */
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = EINVAL;
    return(-1);
  }

  ttystate = RAW;
  ttysavefd = fd;
  return(0);
}

int
tty_reset(int fd)      /* restore terminal's mode */
{
  if (ttystate == RESET)
    return(0);
  if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
    return(-1);
  ttystate = RESET;
  return(0);
}
void
tty_atexit(void)        /* can be set up by atexit(tty_atexit) */
{
  if (ttysavefd >= 0)
    tty_reset(ttysavefd);
}

struct termios *
tty_termios(void)       /* let caller see original tty state */
{
  return(&save_termios);
}

static void
sig_catch(int signo)
{
  printf("signal caught\n");
  tty_reset(STDIN_FILENO);
  exit(0);
}

int
main(void)
{
  int    i;
  char   c;

  if (signal(SIGINT, sig_catch) == SIG_ERR)   /* catch signals */
    printf("signal(SIGINT) error");
  if (signal(SIGQUIT, sig_catch) == SIG_ERR)
    printf("signal(SIGQUIT) error");
  if (signal(SIGTERM, sig_catch) == SIG_ERR)
    printf("signal(SIGTERM) error");

  if (tty_raw(STDIN_FILENO) < 0)
    printf("tty_raw error");
  printf("Enter raw mode characters, terminate with DELETE\n");
  while ((i = read(STDIN_FILENO, &c, 1)) == 1) {
    if ((c &= 255) == 0177)     /* 0177 = ASCII DELETE */
      break;
    printf("%o\n", c);
  }
  if (tty_reset(STDIN_FILENO) < 0)
    printf("tty_reset error");
  if (i <= 0)
    printf("read error");
  if (tty_cbreak(STDIN_FILENO) < 0)
    printf("tty_cbreak error");
  printf("\nEnter cbreak mode characters, terminate with SIGINT\n");
  while ((i = read(STDIN_FILENO, &c, 1)) == 1) {
    c &= 255;
    printf("%o\n", c);
  }
  if (tty_reset(STDIN_FILENO) < 0)
    printf("tty_reset error");
  if (i <= 0)
    printf("read error");
  exit(0);
}

