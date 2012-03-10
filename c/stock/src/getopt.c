#include <stdio.h>		/* for printf */
#include <stdlib.h>		/* for exit */
#include <getopt.h>

int main(int argc, char **argv)
{
	int c;
	int digit_optind = 0;

	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"help", 1, 0, 'h'},
			{"history", 1, 0, 'H'},
			{"industry", 0, 0, 'i'},
			{"version", 0, 0, 'v'},
			{"sector", 0, 0, 's'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "hH::ivs",
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
			printf("option h\n");
			break;

		case 'H':
		  if (optarg)
			printf("option c with value `%s'\n", optarg);
			break;

		case 'i':
			printf("option i\n");
			break;

		case 'v':
			printf("option v\n");
			break;

		case 's':
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
	exit(0);
}
