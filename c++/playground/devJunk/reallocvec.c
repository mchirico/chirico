/*
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
} Conf_Buf;

Conf_Buf *
build(Conf_Buf * c, char *key, char *val)
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

	if (c == NULL) {
		c = (Conf_Buf *) malloc(sizeof(Conf_Buf));
		if (c == NULL)
			return NULL;
		c->key = NULL;
		c->val = NULL;
		c->argc = 0;
	}
	c->argc = c->argc + 1;
	t = realloc(c->key, sizeof(char *) * c->argc);
	if (t == NULL)
		return NULL;

	t[c->argc - 1] = s;
	c->key = t;

	t = realloc(c->val, sizeof(char *) * c->argc);
	if (t == NULL)
		return NULL;
	t[c->argc - 1] = v;
	c->val = t;

	return c;
}

void
pr(Conf_Buf * c)
{
	int i;

	if (c == NULL)
		return;
	for (i = 0; i < c->argc; ++i)
		printf("%s->%s\n", c->key[i], c->val[i]);

	return;
}

void
myfree(Conf_Buf * c)
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

char *
find(Conf_Buf * c, char *s)
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
	Conf_Buf *c = NULL;
        char *f;

	c = build(c, "one", "1");
	c = build(c, "two", "2");
	c = build(c, "three", "3");
	c = build(c, "four", "4");
	pr(c);

        f=(char *) malloc(sizeof(char)*80);
        strcpy(f,"two");
	fprintf(stderr, "find(c,%s)=%s\n", f, find(c, f));
        strcpy(f,"four");
	fprintf(stderr, "find(c,%s)=%s\n", f, find(c, f));
        free(f);
	myfree(c);

	return 0;
}
