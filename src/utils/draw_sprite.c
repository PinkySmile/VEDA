#include <SFML/Graphics.h>
#include "globals.h"

void	image(sfSprite *sprite, int x, int y, int width, int height)
{
	sfVector2f	pos = {x * game.settings.baseScale.x, y * game.settings.baseScale.y};
	sfIntRect	rect;
	sfVector2f	scale;

	if (sprite && sfSprite_getTexture(sprite)) {
		rect = sfSprite_getTextureRect(sprite);
		scale = (sfVector2f){width * game.settings.baseScale.x / rect.width, height * game.settings.baseScale.y / rect.height};
		if (width == -1)
			scale.x = game.settings.baseScale.x;
		if (height == -1)
			scale.y = game.settings.baseScale.y;
		sfSprite_setScale(sprite, scale);
		sfSprite_setPosition(sprite, pos);
		sfRenderWindow_drawSprite(game.ressources.window, sprite, NULL);
	}
}