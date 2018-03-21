#include "structs.h"

void	setFont(sfText *text, sfFont *font)
{
	if (font && text)
		sfText_setFont(text, font);
}

void	rect(game_t *game, int x, int y, int width, int height)
{
	sfVector2f	pos = {x * game->baseScale.x, y * game->baseScale.y};
	sfVector2f	size = {width * game->baseScale.x, height * game->baseScale.y};

	sfRectangleShape_setPosition(game->rectangle, pos);
	sfRectangleShape_setSize(game->rectangle, size);
	sfRenderWindow_drawRectangleShape(game->window, game->rectangle, NULL);
}
void	image(game_t *game, sfSprite *sprite, int x, int y, int width, int height)
{
	sfVector2f	pos = {x * game->baseScale.x, y * game->baseScale.y};
	sfVector2u	size;
	sfVector2f	scale;
	
	if (sprite && sfSprite_getTexture(sprite)) {
		size = sfTexture_getSize(sfSprite_getTexture(sprite)); 
		scale = (sfVector2f){width / size.x * game->baseScale.x, height / size.y * game->baseScale.y};
		if (width == -1)
			scale.x = game->baseScale.x;
		if (height == -1)
			scale.y = game->baseScale.y;
		sfSprite_setScale(sprite, scale);
		sfSprite_setPosition(sprite, pos);
		sfRenderWindow_drawSprite(game->window, sprite, NULL);
	}
}
