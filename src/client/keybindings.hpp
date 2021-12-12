#ifndef __KEYBINDINGS_H_
#define __KEYBINDINGS_H_

#include <SDL2/SDL_scancode.h>

typedef enum {
	MOVE_UP,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	INTERACT_PRIMARY,
	INTERACT_SECONDARY,
	ESCAPE
} keytype_t;

void load_keybindings(SDL_Scancode *);

#endif /* !__KEYBINDINGS_H_ */
