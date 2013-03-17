/* vector.c --

  The MIT License (MIT)
  Copyright (c) 2005 Mike Chirico mchirico@gmail.com
  https://github.com/mchirico


  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This works a bit like C++'s vector.


*/

#include <stdio.h>
#include <stdlib.h>
#if !defined(__APPLE__)
#include <malloc.h>
#endif
#include <string.h>

typedef struct {
    char **key;
    char **val;
    int argc;
} Key_val;

typedef struct {
    char **key;
    Key_val **val;
    int argc;
} Vec;

Vec *vecAdd(Vec * c, const char *key, Key_val * val);
Key_val *keyAdd(Key_val * c, const char *key, const char *val);
void pr(Key_val * c);
void prV(Vec * c);
void myfree(Key_val * c);
void myfreeV(Vec * c);
char *find(Key_val * c, const char *s);
Key_val *findK(Vec * c, const char *s);
int pvLength(Vec * c);
int modify(Key_val * c, const char *s,const char *new_val);
Key_val *getK(Vec * c, int index);

Vec * vecAdd(Vec * c, const char *key, Key_val * val)
{

    char *s = NULL;
    Key_val *v = NULL;
    char **t = NULL;
    Key_val **tC = NULL;

    s = (char *)malloc(sizeof(char) * (strlen(key) + 1));
    if (s == NULL)
	return NULL;

    v = val;

    strcpy(s, key);

    if (c == NULL) {
	c = (Vec *) malloc(sizeof(Vec));
	if (c == NULL)
	    return NULL;
	c->key = NULL;
	c->val = NULL;
	c->argc = 0;
    }
    c->argc = c->argc + 1;
    t = (char **)realloc(c->key,
			 sizeof(char *) * (long unsigned int)c->argc);
    if (t == NULL)
	return NULL;

    t[c->argc - 1] = s;
    c->key = t;

    tC = realloc(c->val, sizeof(Key_val *) * (long unsigned int)c->argc);
    if (tC == NULL)
	return NULL;
    tC[c->argc - 1] = v;
    c->val = tC;

    return c;
}

Key_val *keyAdd(Key_val * c, const char *key, const char *val)
{

    char *s = NULL;
    char *v = NULL;
    char **t = NULL;

    s = (char *)malloc(sizeof(char) * (strlen(key) + 1));
    if (s == NULL)
	return NULL;
    v = (char *)malloc(sizeof(char) * (strlen(val) + 1));
    if (v == NULL)
	return NULL;

    strcpy(s, key);
    strcpy(v, val);

    if (c == NULL) {
	c = (Key_val *) malloc(sizeof(Key_val));
	if (c == NULL)
	    return NULL;
	c->key = NULL;
	c->val = NULL;
	c->argc = 0;
    }
    c->argc = c->argc + 1;
    t = realloc(c->key, sizeof(char *) * (long unsigned int)c->argc);
    if (t == NULL)
	return NULL;

    t[c->argc - 1] = s;
    c->key = t;

    t = realloc(c->val, sizeof(char *) * (long unsigned int)c->argc);
    if (t == NULL)
	return NULL;
    t[c->argc - 1] = v;
    c->val = t;

    return c;
}

void pr(Key_val * c)
{
    int i;

    if (c == NULL)
	return;
    for (i = 0; i < c->argc; ++i)
	printf("%s->%s\n", c->key[i], c->val[i]);

    return;
}

void prV(Vec * c)
{
    int i;

    if (c == NULL)
	return;
    for (i = 0; i < c->argc; ++i) {
	printf("[%s]=>\n", c->key[i]);
	pr(c->val[i]);
	printf("\n\n");

    }

    return;
}

int pvLength(Vec * c)
{
    return c->argc;
}

void myfree(Key_val * c)
{
    if (c == NULL)
	return;

    int i;
    for (i = 0; i < c->argc; ++i) {
	free(c->key[i]);
	free(c->val[i]);
    }
    free(c->key);
    free(c->val);
    free(c);

}

void myfreeV(Vec * c)
{
    if (c == NULL)
	return;

    int i;
    for (i = 0; i < c->argc; ++i) {
	free(c->key[i]);
	myfree(c->val[i]);
    }
    free(c->key);
    free(c->val);
    free(c);

}

char * find(Key_val * c, const char *s)
{
    int i;
    for (i = 0; i < c->argc; ++i) {
	if (strcmp(c->key[i], s) == 0)
	    return c->val[i];
    }

    return NULL;
}



int modify(Key_val * c, const char *s,const char *new_val)
{
    int i;
    char *t = NULL;
    for (i = 0; i < c->argc; ++i) {
	if (strcmp(c->key[i], s) == 0)
	  {
	    t = realloc(c->val[i], sizeof(char *) * (strlen(new_val)));
	    strcpy(t,new_val);
	    c->val[i]=t;
	    return 1;
	  }
    }

    return 0;
}



/*
   Find a particular key_val in a vector given
   a vector key.
 */
Key_val * findK(Vec * c, const char *s)
{
    int i;
    for (i = 0; i < c->argc; ++i)
	if (strcmp(c->key[i], s) == 0)
	    return c->val[i];

    return NULL;
}

Key_val *
 getK(Vec * c, int i)
{

    if (i >= 0 && i < c->argc)
	return c->val[i];

    return NULL;
}

int main(void)
{
    Key_val *k = NULL;
    Vec *v = NULL;
    char *s;
    char ts[] = "one";
    int i = 0;

    k = keyAdd(k, ts, "1");
    k = keyAdd(k, "two", "2");
    k = keyAdd(k, "three", "3");
    k = keyAdd(k, "four", "4");
    k = keyAdd(k, "five", "5");
    v = vecAdd(v, "ONE", k);
    //This doesn_t have to be last but k
    // must have a value. So it can_t go first.

	// You need to reset k
	k = NULL;
    k = keyAdd(k, "twenty one", "21");
    k = keyAdd(k, "twenty two", "22");
    k = keyAdd(k, "twenty three", "23");
    k = keyAdd(k, "twenty four", "24");
    v = vecAdd(v, "TWO", k);

    prV(v);

    printf("\n\n ................ \n\n");

    //Example returning key_val from the string found in vector v
	printf("Below pr(findK(v,\"ONE\"))\n");
    pr(findK(v, "ONE"));

    printf("Below pr(findK(v,\"TWO\"))\n");
    pr(findK(v, "TWO"));



    printf("\n");
    s = (char *)malloc(sizeof(char) * 80);
    strcpy(s, "twenty two");
    fprintf(stderr, "find(c,%s)=%s\n", s, find(k, s));
    modify(k,s,"New twenty two");

    k = findK(v, "ONE");
    strcpy(s, "one");
    fprintf(stderr, "find(c,%s)=%s\n", s, find(k, s));
    free(s);

    printf("\n\nExample use in a for loop.\n\n");
    for (i = 0; i < pvLength(v); ++i) {
	pr(getK(v, i));
	printf("......\n");

    }

    myfreeV(v);
    //Note myfreeV calls this
	// myfree(k);

    return 0;
}
