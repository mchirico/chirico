/*  Copyright (C) GPL 2006 by Mike Chirico <mchirico@gmail.com>
    Version: 0.0.15
    Updated: Thu Sep  6 16:01:36 EDT 2007

     Example usage:

          ./stock <ticker symbol>
     or
          ./stock AAPL
            "AAPL",30.40,"7/8/2004","10:41am",+0.01,30.13,30.50,29.95,908979

     To get all stock in DJI

        ./stock "^DJI,AA,GE,JNJ,MSFT,AXP,GM,JPM,PG,BA,HD,KO,SBC,C,HON,MCD,T,CAT,HP,MMM,UTX,DD,IBM,MO,WMT,DIS,INTC,MRK,XOM,EK,IP"


     Reference:
      http://souptonuts.sourceforge.net/chirico/test.php
      http://souptonuts.sourceforge.net/code/test.php.html

     Download:
      http://sourceforge.net/project/showfiles.php?group_id=79066&package_id=195382&release_id=428043


     SVN:
      The following can be down from the command line to get the latest development version.

      $ svn co https://cpearls.svn.sourceforge.net/svnroot/cpearls stock
        


*/

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <getopt.h>

#define SA      struct sockaddr
#define MAXLINE 4096
#define NUM_BLK 20
#define MAXSUB  1024
#define URL_LEN 256
#define I_LEN   256
#define H_LEN   64
#define D_LEN   32
#define S_LEN   75


#define STARTYR   2003
#define ENDYR     2004
#define ICHK      20




#define LISTENQ         1024

extern int h_errno;



int
Socket (int family, int type, int protocol)
{
  int n;

  if ((n = socket (family, type, protocol)) < 0)
    fprintf (stderr, "socket error: socket(%d,%d,%d)\n", family,
	     type, protocol);
  return (n);
}

void
Connect (int fd, const struct sockaddr *sa, socklen_t salen)
{
  if (connect (fd, sa, salen) < 0)
    fprintf (stderr, "connect error:\n");

}

void
Close (int fp)
{
  int error;
  // Restart close should a signal occur */
  while (((error = close (fp)) == -1) && (errno == EINTR));
  if (error == -1)
    fprintf (stderr, "Failed to close the file in close statement\n");

}



ssize_t
process_http_get (int sockfd, char *host, char *page)
{
  char sendline[MAXLINE + 1], recvline[MAXLINE + 1], buf[NUM_BLK * MAXLINE + 1];	// NUM_BLK*MAXLINE needs to be checked. Could cut data.
  ssize_t n;
  unsigned int i;

  snprintf (sendline, MAXSUB,
	    "GET %s HTTP/1.0\r\n"
	    "Connection: Keep-Alive\r\n"
	    "Pragma: no-cache\r\n"
	    "Host: %s\r\n"
	    "Accept: www/source\r\n"
	    "Accept: application/octet-stream\r\n"
	    "Accept: text/html\r\n\r\n", page, host);


  write (sockfd, sendline, strlen (sendline));
  buf[0] = '\0';
  while ((n = read (sockfd, recvline, MAXLINE)) > 0)
    {
      recvline[n] = '\0';
      if ((strlen (buf) + n) < (NUM_BLK * MAXLINE))
	strncat (buf, recvline, MAXLINE);

    }

  /* We're calling this from the shell. We don't want any
     html headers. Data starts after \r\n\r\n */
  for (i = 0; i < (strlen (buf) + 4); ++i)
    {
      if (buf[i] == '\r' && buf[i + 1] == '\n'
	  && buf[i + 2] == '\r' && buf[i + 3] == '\n')
	{
	  printf ("%s", &buf[i + 4]);
	}
    }

  return n;

}

/* This is for debugging */
int
inputcheck (int argc, char **argv)
{
  int i;
  for (i = 0; i <= argc; ++i)
    {
      printf ("argv[%d]=%s\n", i, argv[i]);
    }
}



int
history (int argc, char **argv, int optind, char *date, int flags)
{

  int sockfd;
  struct sockaddr_in servaddr;
  int n;
  char **pptr;
  char ichk[ICHK + 1];


  // Start month day year 
  char smonth[3], sday[3], syear[5];
  // End month day year
  char month[3], day[3], year[5];
  struct timeval tv;

  time_t curtime;

  gettimeofday (&tv, NULL);
  curtime = tv.tv_sec;


  // mmddyyyy
  if (strlen (date) == 8)
    {
      snprintf (smonth, 3, "%s", date);
      snprintf (sday, 3, "%s", &date[2]);
      snprintf (syear, 5, "%s", &date[4]);
    }
  else
    {
      fprintf (stderr, "Invalid date .. try ./stock -H '00012000'\n");

    }

  strftime (month, 3, "%m", localtime (&curtime));
  strftime (day, 3, "%d", localtime (&curtime));
  strftime (year, 5, "%Y", localtime (&curtime));
  //fprintf(stderr, " %s-%s-%s\n", month, day, year);
  /*
     http://ichart.finance.yahoo.com/table.csv?s=RHT&a=07&b=11&c=1999&d=08&e=6&f=2007&g=d&ignore=.csv
   */
  char *hname = "ichart.finance.yahoo.com";
  char page[URL_LEN + 1];


  if (optind < argc)
    {
      while (optind < argc)
	{
	  printf ("(stock: %s, date: %s)\n", argv[optind], date);

	  snprintf (page, URL_LEN,
		    "/table.csv?s=%s&a=%d&b=%s&c=%s&d=%d&e=%s&f=%s&g=d&ignore=.csv",
		    argv[optind], atoi (smonth) - 1, sday,
		    syear, atoi (month) - 1, day, year);


/*
			   The following  6/2/2004 to 6/11/2004

                                                                   v----v-----v------------- 9/17/2004
http://ichart.finance.yahoo.com/table.csv?s=AAPL&a=00&b=2&c=2003&d=9&e=17&f=04&g=d&ignore=.csv
                                                    ^----^---^---  0/2/2003   from



*/


	  char str[50];
	  struct hostent *hptr;
	  if ((hptr = gethostbyname (hname)) == NULL)
	    {
	      fprintf (stderr,
		       " gethostbyname error for host: %s: %s",
		       hname, hstrerror (h_errno));
	      exit (1);
	    }
	  //printf("hostname: %s\n", hptr->h_name);
	  if (hptr->h_addrtype == AF_INET
	      && (pptr = hptr->h_addr_list) != NULL)
	    {

	      inet_ntop (hptr->h_addrtype, *pptr, str, sizeof (str));
	    }
	  else
	    {
	      fprintf (stderr, "Error call inet_ntop \n");
	    }

	  sockfd = Socket (AF_INET, SOCK_STREAM, 0);
	  bzero (&servaddr, sizeof (servaddr));
	  servaddr.sin_family = AF_INET;
	  servaddr.sin_port = htons (80);
	  inet_pton (AF_INET, str, &servaddr.sin_addr);

	  Connect (sockfd, (SA *) & servaddr, sizeof (servaddr));
	  //fprintf(stderr, "%s%s", hname, page);
	  n = process_http_get (sockfd, hname, page);
	  Close (sockfd);

	  optind++;
	}			//end while
    }



}				// end history


int
site_page (char *_hname, char *_page)
{

  int sockfd;
  struct sockaddr_in servaddr;

  char **pptr;

  char hname[H_LEN + 1];
  char page[URL_LEN + 1];

  // industry

  //      snprintf(hname, H_LEN, "%s", "biz.yahoo.com");
  //      snprintf(page, URL_LEN, "%s", "/p/csv/sum_conameu.csv");

  snprintf (hname, H_LEN, "%s", _hname);
  snprintf (page, URL_LEN, "%s", _page);


  char str[50];
  struct hostent *hptr;
  if ((hptr = gethostbyname (hname)) == NULL)
    {
      fprintf (stderr, " gethostbyname error for host: %s: %s",
	       hname, hstrerror (h_errno));
      exit (1);
    }
  //printf("hostname: %s\n", hptr->h_name);
  if (hptr->h_addrtype == AF_INET && (pptr = hptr->h_addr_list) != NULL)
    {

      inet_ntop (hptr->h_addrtype, *pptr, str, sizeof (str));
    }
  else
    {
      fprintf (stderr, "Error call inet_ntop \n");
    }


  sockfd = Socket (AF_INET, SOCK_STREAM, 0);
  bzero (&servaddr, sizeof (servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons (80);
  inet_pton (AF_INET, str, &servaddr.sin_addr);

  Connect (sockfd, (SA *) & servaddr, sizeof (servaddr));
  process_http_get (sockfd, hname, page);
  Close (sockfd);


}

/* There is a loop here. Gets last price for all stocks */
int
last_price (int argc, char **argv, int optind, int flags)
{

  int sockfd;
  struct sockaddr_in servaddr;

  char **pptr;

  char hname[H_LEN + 1];
  char page[URL_LEN + 1];

  // sector
  /*
     switch (flags) {

     case (0x3):
     snprintf(hname, H_LEN, "%s", "biz.yahoo.com");
     snprintf(page, URL_LEN, "%s", "/p/csv/s_conamed.csv");
     break;
     case (0x4):
     snprintf(hname, H_LEN, "%s", "biz.yahoo.com");
     snprintf(page, URL_LEN, "%s", "/p/csv/sum_conameu.csv");
     break;
     default:
   */
  snprintf (hname, H_LEN, "%s", "download.finance.yahoo.com");


  char str[50];
  struct hostent *hptr;
  if ((hptr = gethostbyname (hname)) == NULL)
    {
      fprintf (stderr, " gethostbyname error for host: %s: %s",
	       hname, hstrerror (h_errno));
      exit (1);
    }
  //printf("hostname: %s\n", hptr->h_name);
  if (hptr->h_addrtype == AF_INET && (pptr = hptr->h_addr_list) != NULL)
    {

      inet_ntop (hptr->h_addrtype, *pptr, str, sizeof (str));
    }
  else
    {
      fprintf (stderr, "Error call inet_ntop \n");
    }

  if (optind < argc)
    {
      while (optind < argc)
	{

	  snprintf (page, URL_LEN,
		    "/d/quotes.cvs?s=%s&f=sl1d1t1c1ohgv", argv[optind]);

	  sockfd = Socket (AF_INET, SOCK_STREAM, 0);
	  bzero (&servaddr, sizeof (servaddr));
	  servaddr.sin_family = AF_INET;
	  servaddr.sin_port = htons (80);
	  inet_pton (AF_INET, str, &servaddr.sin_addr);

	  Connect (sockfd, (SA *) & servaddr, sizeof (servaddr));
	  process_http_get (sockfd, hname, page);
	  Close (sockfd);
	  optind++;
	}
    }

}

int
input (int argc, char **argv)
{
  int i = 0;
  for (i = 0; i <= argc; ++i)
    {
      printf ("argv[%d]=%s\n", i, argv[i]);
    }
}



int
sector_cut (char *sector)
{

  int i = 0;
  char *s_array[] = {
    "Basic Materials",
    "Conglomerates",
    "Consumer Goods",
    "Financial",
    "Healthcare",
    "Industrial Goods",
    "Services",
    "Technology",
    "Utilities",		// End Main Sector
    "Agricultural Chemicals",
    "Aluminum",
    "Chemicals - Major Diversified",
    "Copper",
    "Gold",
    "Independent Oil & Gas",
    "Industrial Metals & Minerals",
    "Major Integrated Oil & Gas",
    "Nonmetallic Mineral Mining",
    "Oil & Gas Drilling & Exploration",
    "Oil & Gas Equipment & Services",
    "Oil & Gas Pipelines",
    "Oil & Gas Refining & Marketing",
    "Silver",
    "Specialty Chemicals",
    "Steel & Iron",
    "Synthetics",
    '\0'
  };

  char *p_array[] = {

    "/p/csv/1conameu.csv",
    "/p/csv/2conameu.csv",
    "/p/csv/3conameu.csv",
    "/p/csv/4conameu.csv",
    "/p/csv/5conameu.csv",
    "/p/csv/6conameu.csv",
    "/p/csv/7conameu.csv",
    "/p/csv/8conameu.csv",
    "/p/csv/9conameu.csv",	// End Main Sector
    "/p/csv/112conameu.csv",
    "/p/csv/132conameu.csv",
    "/p/csv/110conameu.csv",
    "/p/csv/131conameu.csv",
    "/p/csv/134conameu.csv",
    "/p/csv/121conameu.csv",
    "/p/csv/133conameu.csv",
    "/p/csv/120conameu.csv",
    "/p/csv/136conameu.csv",
    "/p/csv/123conameu.csv",
    "/p/csv/124conameu.csv",
    "/p/csv/125conameu.csv",
    "/p/csv/122conameu.csv",
    "/p/csv/135conameu.csv",
    "/p/csv/113conameu.csv",
    "/p/csv/130conameu.csv",
    "/p/csv/111conameu.csv",
    '\0'
  };


  for (i = 0; s_array[i] != '\0'; ++i)
    {
      if (!strcmp (s_array[i], sector))
	{
	  site_page ("biz.yahoo.com", p_array[i]);
	}
    }
  return 1;

}




int
main (int argc, char **argv)
{

  int flags = 0, digit_optind = 0, c;
  char ibuf[I_LEN + 1];
  char date[D_LEN + 1] = "";
  char sector[S_LEN + 1] = "";


  while (1)
    {
      int this_option_optind = optind ? optind : 1;
      int option_index = 0;
      static struct option long_options[] = {
	{"help", 1, 0, 'h'},
	{"history", 1, 0, 'H'},
	{"industry", 0, 0, 'i'},
	{"version", 0, 0, 0},
	{"sector", 0, 0, 's'},
	{"sectorsub", 1, 0, 'S'},
	{0, 0, 0, 0}
      };

      c = getopt_long (argc, argv, "hH:ivsS:", long_options, &option_index);
      if (c == -1)
	break;

      switch (c)
	{

	case 'h':
	  flags |= 0x1;
	  fprintf (stderr,
		   "Copyright (C) GPL 2006 by Mike Chirico <mchirico@gmail.com>\n");
	  fprintf (stderr,
		   "\nUsage: stock <Nasdaq Ticker|[,Tickers]>\n"
		   " Tickers are case insensitive\n\n"
		   "  $ stock rht\n or\n"
		   "  $ stock \"^DJI,AA,GE,JNJ,MSFT,AXP,GM,JPM,\\\n"
		   "PG,BA,HD,KO,SBC,C,HON,MCD,T,CAT,HP,MMM,UTX,DD,IBM,MO,WMT,DIS,INTC,MRK,XOM,EK,IP\"\n\n");
	  break;

	case 'H':
	  flags |= 0x2;
	  // Format from date "+%m%d%Y"
	  //    01121963
	  if (optarg)
	    {
	      snprintf (date, D_LEN, "%s", optarg);
	    }
	  break;

	case 'i':
	  flags |= 0x4;
	  break;

	case 'v':
	  flags |= 0x8;
	  printf
	    ("Copyright (C) GPL 2006 by Mike Chirico\n<mchirico@gmail.com>\n");
	  printf ("version 0.0.26\n\n");
	  printf
	    ("File download:\n http://prdownloads.sourceforge.net/cpearls/stock.tar.gz?download\n\n");
	  printf ("Subversion:\n"
		  " http://chirico.googlecode.com/svn/trunk/c/stock/\n\n"
		  " svn checkout http://chirico.googlecode.com/svn/trunk/c/stock/ stock\n\n"
		  "Download:"
		  "http://code.google.com/p/chirico/downloads/list?can=2&q=stock&colspec=Filename+Summary+Uploaded+Size+DownloadCount\n\n");
	  exit (0);
	  break;

	case 's':
	  flags |= 0x10;
	  break;

	case 'S':
	  flags |= 0x100;
	  if (optarg)
	    {
	      snprintf (sector, S_LEN, "%s", optarg);
	    }
	  break;

	case '?':
	  fprintf (stderr, "Unrecognized option  \n");
	  break;

	default:
	  printf ("?? getopt returned character code 0%o ??\n", c);
	}
    }



  //Combination of flags
  switch (flags)
    {
    case 0x0:
      last_price (argc, argv, optind, flags);
      break;

    case 0x2:
      history (argc, argv, optind, date, flags);
      break;

    case 0x4:
      site_page ("biz.yahoo.com", "/p/csv/sum_conameu.csv");
      break;

    case 0x10:
      site_page ("biz.yahoo.com", "/p/csv/s_conameu.csv");
      break;

    case 0x100:
      sector_cut (sector);
      break;
    }


  if (argc == 1)
    {
      printf ("(version 0.0.15)\n"
	      "Example Usage:\n"
	      "  $ stock rht\n"
	      "  $ stock rht -H `date -d '-10 day' %s\n",
	      "'+\%m\%d\%Y'`\n" "  $ stock -i\n");

    }
  exit (0);

}
