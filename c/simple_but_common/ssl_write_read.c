/*
  Example of ssl read and write to a file

  gcc ssl_write_read.c -lssl
  ./a.out


*/



#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

int write_data(const char *filename, char *out, int len, unsigned char *key)
{
  int total, written;
  BIO *cipher, *b64, *buffer, *file;
 
  /* Create a buffered file BIO for writing */
  file = BIO_new_file(filename, "w");
  if (!file)
    return 0;
 
  /* Create a buffering filter BIO to buffer writes to the file */
  buffer = BIO_new(BIO_f_buffer(  ));
 
  /* Create a base64 encoding filter BIO */
  b64 = BIO_new(BIO_f_base64(  ));
 
  /* Create the cipher filter BIO and set the key.  The last parameter of
     BIO_set_cipher is 1 for encryption and 0 for decryption */
  cipher = BIO_new(BIO_f_cipher(  ));
  BIO_set_cipher(cipher, EVP_des_ede3_cbc(  ), key, NULL, 1);
 
  /* Assemble the BIO chain to be in the order cipher-b64-buffer-file */
  BIO_push(cipher, b64);
  BIO_push(b64, buffer);
  BIO_push(buffer, file);
 
  /* This loop writes the data to the file.  It checks for errors as if the
     underlying file were non-blocking */
  for (total = 0;  total < len;  total += written)
    {
      if ((written = BIO_write(cipher, out + total, len - total)) <= 0)
        {
	  if (BIO_should_retry(cipher))
            {
	      written = 0;
	      continue;
            }
	  break;
        }
    }
 
  /* Ensure all of our data is pushed all the way to the file */
  BIO_flush(cipher);
 
  BIO_free_all(cipher);
}

int  read_data(const char *filename, char **p, int len, unsigned char *key)
{
  int total, written;
  BIO *cipher, *b64, *buffer, *file;
  char *b = malloc(len);
 
  /* Create a buffered file BIO for reading */
  file = BIO_new_file(filename, "r");
  if (!file)
    return 0;
 
  /* Create a buffering filter BIO to buffer writes to the file */
  buffer = BIO_new(BIO_f_buffer(  ));
 
  /* Create a base64 encoding filter BIO */
  b64 = BIO_new(BIO_f_base64(  ));
 
  /* Create the cipher filter BIO and set the key.  The last parameter of
     BIO_set_cipher is 1 for encryption and 0 for decryption */
  cipher = BIO_new(BIO_f_cipher(  ));
  BIO_set_cipher(cipher, EVP_des_ede3_cbc(  ), key, NULL, 0);
 
  /* Assemble the BIO chain to be in the order cipher-b64-buffer-file */
  BIO_push(cipher, b64);
  BIO_push(b64, buffer);
  BIO_push(buffer, file);
 
  /* This loop writes the data to the file.  It checks for errors as if the
     underlying file were non-blocking */
  for (total = 0;  total < len;  total += written)
    {
      if ((written = BIO_read(cipher, b, len - total)) <= 0)
        {
	  if (BIO_should_retry(cipher))
            {
	      written = 0;
	      continue;
            }
	  break;
        }
    }
 
  b[total]='\0';
  fprintf(stderr,"%s\n",b);
  *p=b;
  /* Ensure all of our data is pushed all the way to the file */
  BIO_flush(cipher);
 
  BIO_free_all(cipher);
}

int main(void)
{
  char *p;
  char *file="Encrypted_data.txt";
  printf("\nThis program write encrypted data to %s\n",file);
  printf("\nThen reads the data back\n\n");


  char *data="this is sample data";
  write_data(file, data, strlen(data), "mykey");
  read_data(file,&p, 2048, "mykey");


  printf("%s\n",p);
  free(p);

}
