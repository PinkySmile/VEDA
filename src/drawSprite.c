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
	sfIntRect	rect;
	sfVector2f	scale;
	
	if (sprite && sfSprite_getTexture(sprite)) {
		rect = sfSprite_getTextureRect(sprite);
		scale = (sfVector2f){width / rect.width * game->baseScale.x, height / rect.height * game->baseScale.y};
		if (width == -1)
			scale.x = game->baseScale.x;
		if (height == -1)
			scale.y = game->baseScale.y;
		sfSprite_setScale(sprite, scale);
		sfSprite_setPosition(sprite, pos);
		sfRenderWindow_drawSprite(game->window, sprite, NULL);
	}
}

void	text(char *str, game_t *game, int x, int y)
{
	sfVector2f	pos = {x * game->baseScale.x, y * game->baseScale.y};

	if (str && sfText_getFont(game->text)) {
		sfText_setString(game->text, str);
		sfText_setPosition(game->text, pos);
		sfText_setScale(game->text, game->baseScale);
		sfRenderWindow_drawText(game->window, game->text, 0);
	}
}