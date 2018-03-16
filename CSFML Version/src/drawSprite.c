#include "structs.h"

void	image(game_t *game, sfSprite *sprite, int x, int y)
{
	sfVector2f	pos = {x, y};
	
	if (sprite) {
		sfSprite_setPosition(sprite, pos);
		sfRenderWindow_drawSprite(game->window, sprite, NULL);
	}
}