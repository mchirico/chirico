/*  Copyright (c) GPL mchirico@users.sourceforge.net
    This is an example of using getopt_long with flags.
    It may be necessary to take actions based on a combination
    of options.

*/


#include <stdio.h>		/* for printf */
#include <stdlib.h>		/* for exit */
#include <getopt.h>

int main(int argc, char **argv)
{
	int c;
	int flags =0;

	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"help", 1, 0, 'h'},
			{"history", 1, 0, 'H'},
			{"industry", 0, 0, 'i'},
			{"version", 0, 0, 'v'},
			{"sector", 0, 0, 's'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "hH:ivs",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			printf("option %s",
			       long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;

		case 'h':
		        flags |= 0x1;
			printf("option h\n");
			break;

		case 'H':
		        flags |= 0x2;
			printf("option c with value `%s'\n", optarg);
			break;

		case 'i':
		        flags |= 0x4;
			printf("option i\n");
			break;

		case 'v':
		        flags |= 0x8;
			printf("option v\n");
			break;

		case 's':
		        flags |= 0x10;
			printf("option s\n");
			break;


		case '?':
			break;

		default:
			printf
			    ("?? getopt returned character code 0%o ??\n",
			     c);
		}
	}

	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}
	printf("argc=%d\n", argc);
        if (flags & 0x1) {
	  printf("h flag\n");
	}
        if (~flags & 0x1){
          printf("no h flag\n");
	}
	exit(0);
}
