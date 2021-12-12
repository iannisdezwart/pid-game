#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>

int
main(int argc, char **argv)
{
	int opt;
	while ((opt = getopt(argc, argv, ":v")) != -1) {
		switch (opt) {
		case 'v':
			puts("PID Game v1.0");
			return EXIT_SUCCESS;
		default:
			fprintf(stderr, "Usage: %s [-v]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	return EXIT_SUCCESS;
}
