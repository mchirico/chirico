/* match.c - Matches a string against a regular expression */

#include <alloca.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void do_regerror(int errcode, const regex_t *preg) { 
    char *errbuf;
    size_t errbuf_size;

    errbuf_size = regerror(errcode, preg, NULL, 0);
    errbuf = alloca(errbuf_size);
    if (!errbuf) {
        perror("alloca");
        return;
    }

    regerror(errcode, preg, errbuf, errbuf_size);
    fprintf(stderr, "%s\n", errbuf);
}

int main() {

    regex_t p;
    regmatch_t *pmatch;
    int rerr;
    char *regex = "(^(.*[^\\])#.*$)|(^[^#]+$)";
    char string[BUFSIZ+1];
    int i;

    if ((rerr = regcomp(&p, regex, REG_EXTENDED | REG_NEWLINE))) {
        do_regerror(rerr, &p);
    }

    pmatch = alloca(sizeof(regmatch_t) * (p.re_nsub+1));
    if (!pmatch) {
        perror("alloca");
    }

    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);

    if ((rerr = regexec(&p, string, p.re_nsub+1, pmatch, 0))) {
        if (rerr == REG_NOMATCH) {
            /* regerror can handle this case, but in most cases
             * it is handled specially
             */
            printf("String did not match %s\n", regex);
        } else {
            do_regerror(rerr, &p);
        }
    } else {
        /* match succeeded */
        printf("String matched regular expressioon %s\n", regex);
        for(i = 0; i <= p.re_nsub; i++) {
            /* print the matching portion(s) of the string */
            if (pmatch[i].rm_so != -1) {
                char *submatch;
                size_t matchlen = pmatch[i].rm_eo - pmatch[i].rm_so;
                submatch = malloc(matchlen+1);
                strncpy(submatch, string+pmatch[i].rm_so, 
			matchlen);
                submatch[matchlen] = '\0';
                printf("matched subexpression %d: %s\n", i, 
		       submatch);
                free(submatch);
            } else {
                printf("no match for subexpression %d\n", i);
            }
        }
    }
    exit(0);
}
