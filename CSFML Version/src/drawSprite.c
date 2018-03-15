#include "structs.h"

void	drawSprite(sfRenderWindow *window, sfSprite *sprite, int x, int y)
{
	sfVector2f	pos = {x, y};
	
	if (sprite) {
		sfSprite_setPosition(sprite, pos);
		sfRenderWindow_drawSprite(window, sprite, NULL);
	}
}