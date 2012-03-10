#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned int gcd(unsigned int u, unsigned int v)
{
  int shift;

  /* GCD(0,x) := x */
  if (u == 0 || v == 0)
    return u | v;

  /* Let shift := lg K, where K is the greatest power of 2
     dividing both u and v. */
  for (shift = 0; ((u | v) & 1) == 0; ++shift) {
    u >>= 1;
    v >>= 1;
  }

  while ((u & 1) == 0)
    u >>= 1;

  /* From here on, u is always odd. */
  do {
    while ((v & 1) == 0)  /* Loop X */
      v >>= 1;

    /* Now u and v are both odd, so diff(u, v) is even.
       Let u = min(u, v), v = diff(u, v)/2. */
    if (u < v) {
      v -= u;
    } else {
      unsigned int diff = u - v;
      u = v;
      v = diff;
    }
    v >>= 1;
  } while (v != 0);

  return u << shift;
}





int main(void) {

  unsigned int i,j,a,t,n,max=1;

  n=2400;
  
  i=10;
  j=5;
  fprintf(stderr,"%ld\n",gcd(1,n));
  t= (unsigned int) n/2.0;
  max=1;
  for(i=2; i<=t; ++i)
    { a=gcd(i,n);
      if (a > max) {
	max=a;
        fprintf(stderr,"%ld\n",max);
      }
    }
  fprintf(stderr,"%ld\n",gcd(n,n));


}
