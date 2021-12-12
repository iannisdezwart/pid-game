#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "keybindings.hpp"

const char *argv0;

static SDL_Window *init_window(void);
static SDL_Renderer *init_renderer(SDL_Window *);

typedef struct {
	float x, y;
} Vec2;

struct {
	SDL_Scancode kb_bindings[7];
	int res_x, res_y;
} settings;

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

SDL_Renderer *
init_renderer(SDL_Window *window)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
		errx(EXIT_FAILURE, "%s: renderer could not be created: %s\n", argv0,
		     SDL_GetError());
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return renderer;
}

bool
handle_input(SDL_Event &event)
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
		const Uint8 *kb_state = SDL_GetKeyboardState(NULL);
		for (int i = 0; i < 7; i++)
			printf("%d %d\n", settings.kb_bindings[i], kb_state[settings.kb_bindings[i]]);
	}
	return true;
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
	SDL_Renderer *renderer = init_renderer(window);

	load_keybindings(settings.kb_bindings);

	SDL_Event event;
	bool running = true;
	while (running) {
		running = handle_input(event);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
