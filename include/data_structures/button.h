#ifndef __BUTTON_HEADER_
#define __BUTTON_HEADER_

#include <SFML/Graphics.h>
#include <stdbool.h>

typedef struct {
	char			*content;
	sfVector2f		pos;
	sfVector2f		size;
	sfColor			color;
	int			shadeStep;
	sfColor			textColor;
	void			(*callback)(int);
	sfRectangleShape	*rect;
	bool			displayed;
	bool			active;
} Button;

#endif