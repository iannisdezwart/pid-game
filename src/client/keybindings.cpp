#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "keybindings.hpp"

void
load_keybindings(SDL_Scancode *kb_bindings)
{
	FILE *fp;
	char action[32];
	SDL_Scancode key;
	const SDL_Scancode default_keys[] = {SDL_SCANCODE_W,           SDL_SCANCODE_A,
	                                     SDL_SCANCODE_D,           SDL_SCANCODE_S,
	                                     SDL_SCANCODE_LEFTBRACKET, SDL_SCANCODE_RIGHTBRACKET,
	                                     SDL_SCANCODE_ESCAPE};

	/* If there is no config file, we default to the default bindings */
	if (!(fp = fopen("input.cfg", "r"))) {
		if (errno == ENOENT) {
			memcpy(kb_bindings, default_keys, sizeof(SDL_Scancode) * 7);
			return;
		}
		err(EXIT_FAILURE, "fopen");
	}

	while (fscanf(fp, "%31s %d", action, &key) != EOF) {
		if (!strcmp(action, "MoveUp"))
			kb_bindings[MOVE_UP] = key;
		else if (!strcmp(action, "MoveLeft"))
			kb_bindings[MOVE_LEFT] = key;
		else if (!strcmp(action, "MoveRight"))
			kb_bindings[MOVE_RIGHT] = key;
		else if (!strcmp(action, "MoveDown"))
			kb_bindings[MOVE_DOWN] = key;
		else if (!strcmp(action, "InteractPrimary"))
			kb_bindings[INTERACT_PRIMARY] = key;
		else if (!strcmp(action, "InteractSecondary"))
			kb_bindings[INTERACT_SECONDARY] = key;
		else if (!strcmp(action, "Escape"))
			kb_bindings[ESCAPE] = key;
		else
			errx(EXIT_FAILURE, "invalid keybind option '%s'", action);
	}
}
