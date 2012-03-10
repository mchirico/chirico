/*
Copyright (c) GPL 2009, Mike Chirico <mchirico@gmail.com>
vector.c

This works a bit like C++'s vector.


*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
	char **key;
	char **val;
	int argc;
} Key_val;

typedef struct
{
	char **key;
	Key_val **val;
	int argc;
} Vec;

Vec *
vecAdd(Vec * vec, char *key, Key_val * kv_in)
{

	char *s = NULL;
	Key_val *kv = NULL;
	char **t = NULL;
	Key_val **tC = NULL;
	int i;

	s = (char *)malloc(sizeof(char) * (strlen(key) + 1));
	if (s == NULL)
		return NULL;

	kv = kv_in;

	strcpy(s, key);

	if (vec == NULL) {
		vec = (Vec *) malloc(sizeof(Vec));
		if (vec == NULL)
			return NULL;
		vec->key = NULL;
		vec->val = NULL;
		vec->argc = 0;
	}
	vec->argc = vec->argc + 1;
	t = realloc(vec->key, sizeof(char *) * vec->argc);
	if (t == NULL)
		return NULL;

	t[vec->argc - 1] = s;
	vec->key = t;

	tC = realloc(vec->val, sizeof(Key_val *) * vec->argc);
	if (tC == NULL)
		return NULL;
	tC[vec->argc - 1] = kv;
	vec->val = tC;

	return vec;
}

Key_val *
keyAdd(Key_val * kv, char *key, char *val)
{

	char *s = NULL;
	char *v = NULL;
	char **t = NULL;
	int i;

	s = (char *)malloc(sizeof(char) * (strlen(key) + 1));
	if (s == NULL)
		return NULL;
	v = (char *)malloc(sizeof(char) * (strlen(val) + 1));
	if (v == NULL)
		return NULL;

	strcpy(s, key);
	strcpy(v, val);

	if (kv == NULL) {
		kv = (Key_val *) malloc(sizeof(Key_val));
		if (kv == NULL)
			return NULL;
		kv->key = NULL;
		kv->val = NULL;
		kv->argc = 0;
	}
	kv->argc = kv->argc + 1;
	t = realloc(kv->key, sizeof(char *) * kv->argc);
	if (t == NULL)
		return NULL;

	t[kv->argc - 1] = s;
	kv->key = t;

	t = realloc(kv->val, sizeof(char *) * kv->argc);
	if (t == NULL)
		return NULL;
	t[kv->argc - 1] = v;
	kv->val = t;

	return kv;
}

void
pr(Key_val * c)
{
	int i;

	if (c == NULL)
		return;
	for (i = 0; i < c->argc; ++i)
		printf("%s->%s\n", c->key[i], c->val[i]);

	return;
}

void
pr2(Vec * c)
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

void
myfree(Key_val * c)
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

void
myfree2(Vec * c)
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

char *
find(Key_val * c, char *s)
{
	int i;
	for (i = 0; i < c->argc; ++i)
		if (strcmp(c->key[i], s) == 0)
			return c->val[i];

	return NULL;
}

int
main(void)
{
	Key_val *k = NULL;
	Vec *v = NULL;
	char *f;

	k = keyAdd(k, "one", "1");
	k = keyAdd(k, "two", "2");
	k = keyAdd(k, "three", "3");
	k = keyAdd(k, "four", "4");
	v = vecAdd(v, "ONE", k);

	k = NULL;
	k = keyAdd(k, "twenty one", "21");
	k = keyAdd(k, "twenty two", "22");
	k = keyAdd(k, "twenty three", "23");
	k = keyAdd(k, "twenty four", "24");
	v = vecAdd(v, "TWO", k);

	pr2(v);

	printf("\n\n ................ \n\n");
	pr(k);
	f = (char *)malloc(sizeof(char) * 80);
	strcpy(f, "two");
	fprintf(stderr, "find(c,%s)=%s\n", f, find(k, f));
	strcpy(f, "four");
	fprintf(stderr, "find(c,%s)=%s\n", f, find(k, f));
	free(f);

	myfree2(v);

	/* Note myfree2 calls this */
	//myfree(k);

	return 0;
}
