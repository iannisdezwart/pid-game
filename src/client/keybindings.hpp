#ifndef __KEYBINDINGS_H_
#define __KEYBINDINGS_H_

typedef enum {
	MOVE_UP,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	INTERACT_PRIMARY,
	INTERACT_SECONDARY,
	ESCAPE
} keytype_t;

SDL_Scancode *load_keybindings(void);

#endif /* !__KEYBINDINGS_H_ */
