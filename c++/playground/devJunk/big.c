/*

man 3 bn
gcc big.c -lssl

*/


#include <openssl/bn.h>
#include <malloc.h>
int main(void)
{

  char *c;
  BIGNUM a, b,d,r;
  BN_init(&a);
  BN_init(&b);
  BN_init(&d);
  BN_init(&r);
  BN_CTX *x = BN_CTX_new(  );

  unsigned long w=342343837382342;
  unsigned long p=898298999999;


  BN_set_word(&a,w);
  BN_set_word(&b,p);
  BN_div(&d, &r, &a, &b, x);
  c=BN_bn2dec(&d);
  printf("%s\n",c);
  free(c);
  c=BN_bn2dec(&r);
  printf("%s\n",c);
  free(c);


  
  BN_free(&a);
  BN_free(&b);
  BN_free(&d);
  BN_free(&r);
  BN_CTX_free(x);

}
