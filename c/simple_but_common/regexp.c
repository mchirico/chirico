/*
  This is the program that appears in Ch1 of ("Beautiful Code", 
  edited by Andy Oram and Greg Wilson. Copyright 2007 O'Reilly Media, 
  Inc., 978-0-596-51004-6.) which is a working regular expression 
  example written by Rob Pike.

  Regular Expression Matcher for the following:

  c Matches any literal character
  . Matches a single character
  ^ Beginning character
  $ Matches the end of an input string
  * Zero or more characters

 




       


 */



#include <stdio.h>
#include <stdlib.h>

int match(char *regexp, char *text);
int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text)
{
	if (regexp[0] == '^')
		return matchhere(regexp + 1, text);
	do {			/* must look even if string is empty */
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return 1;
	if (regexp[1] == '*')
		return matchstar(regexp[0], regexp + 2, text);

	if (regexp[0] == '$' && regexp[1] == '\0')
		return *text == '\0';
	if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
		return matchhere(regexp + 1, text + 1);
	return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
	do {			/* a * matches zero or more instances */
		if (matchhere(regexp, text))
			return 1;
	} while (*text != '\0' && (*text++ == c || c == '.'));
	return 0;
}

int main(void)
{
  if (match("ab*", "one two three ab")) {
		printf("Match\n");
		return 1;
  }
  else {
		printf("No Match\n");
		return 0;

  }


}
