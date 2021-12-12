#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>

const char *argv0;

SDL_Window *
init_window(void)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
			errx(EXIT_FAILURE, "%s: failed to initialize SDL2: %s\n", argv0,
			     SDL_GetError());
	}
	SDL_Window *window = SDL_CreateWindow("PID Game", SDL_WINDOWPOS_UNDEFINED,
	                                      SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		errx(EXIT_FAILURE, "%s: window could not be created: %s\n", argv0, SDL_GetError());
	return window;
}

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

	argv0 = argv[0];
	SDL_Window *window = init_window();

	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
