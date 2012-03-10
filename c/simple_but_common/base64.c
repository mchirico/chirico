/*
   Compile:
      gcc base64.c -o base64 -lssl

*/

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#define BUFLEN 8192
#define READLN 512 /* Must be less than BUFLEN */



void base64m(const char *str, char **p, size_t size)
{

  BIO *bio, *b64, *mem, *a, *b,  *cipher;
  char buf[BUFLEN];

  char *t = malloc(size);

  int n=0,total=0;



  a = BIO_new(BIO_s_bio(  ));
  BIO_set_write_buf_size(a, BUFLEN);
  b = BIO_new(BIO_s_bio(  ));
  BIO_set_write_buf_size(b, BUFLEN);
  BIO_make_bio_pair(a, b);


  b64 = BIO_new(BIO_f_base64());
  BIO_push(b64, a);

  n=BIO_write(b64, str, strlen(str));
  fprintf(stderr,"write %d\n",n);
  
  BIO_flush(b64);
  BIO_pop(b64);

  n = BIO_pending(b);
  fprintf(stderr,"pending %d\n",n);


  while( ( n = BIO_read(b, buf+total, READLN)) > 0 )
    {
      total+=n;
      fprintf(stderr,"total=%d\n",total);
    }

  if (total > 0)
   buf[total -1 ]='\0';
  else
    buf[0]='\0';

  n = BIO_pending(b);
  fprintf(stderr,"pending %d\n",n);

  fprintf(stderr,"After Read in sub: n=%d ->%s<-\n",n,buf);
  snprintf(t,size,"%s",buf);
  *p=t;

  BIO_destroy_bio_pair(a);
  BIO_free_all(a);
  BIO_free_all(b);


}


base64(const char *str)
{
  BIO *bio, *b64;
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new_fp(stdout, BIO_NOCLOSE);
  bio = BIO_push(b64, bio);
  BIO_write(bio, str, strlen(str));
  BIO_flush(bio);

  BIO_free_all(bio);

}




int main(void)
{

  char *p;

  base64m("example message and more too",&p,BUFLEN);
  fprintf(stderr,"\n%s\n",p);


  free(p);
  return 0;



}
