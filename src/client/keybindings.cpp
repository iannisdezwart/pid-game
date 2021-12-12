#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "keybindings.hpp"

SDL_Scancode *
load_keybindings(void)
{
	FILE *fp;
	char action[32];
	SDL_Scancode key;
	static SDL_Scancode keys[7] = {SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,
	                               SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,
	                               SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,
	                               SDL_SCANCODE_UNKNOWN},
			    default_keys[] = {SDL_SCANCODE_W,           SDL_SCANCODE_A,
	                                      SDL_SCANCODE_D,           SDL_SCANCODE_S,
	                                      SDL_SCANCODE_LEFTBRACKET, SDL_SCANCODE_RIGHTBRACKET};

	/* If there is no config file, we default to the default bindings */
	if (!(fp = fopen("input.cfg", "r"))) {
		if (errno == EACCES)
			return default_keys;
		err(EXIT_FAILURE, "fopen");
	}

	while (fscanf(fp, "%31s %d", action, &key) != EOF) {
		if (!strcmp(action, "MoveUp"))
			keys[MOVE_UP] = key;
		else if (!strcmp(action, "MoveLeft"))
			keys[MOVE_LEFT] = key;
		else if (!strcmp(action, "MoveRight"))
			keys[MOVE_RIGHT] = key;
		else if (!strcmp(action, "MoveDown"))
			keys[MOVE_DOWN] = key;
		else if (!strcmp(action, "InteractPrimary"))
			keys[INTERACT_PRIMARY] = key;
		else if (!strcmp(action, "InteractSecondary"))
			keys[INTERACT_SECONDARY] = key;
		else if (!strcmp(action, "Escape"))
			keys[ESCAPE] = key;
		else
			errx(EXIT_FAILURE, "invalid keybind option '%s'", action);
	}

	return keys;
}
