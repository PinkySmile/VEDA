#include "structs.h"

void	setFont(sfText *text, sfFont *font)
{
	if (font && text)
		sfText_setFont(text, font);
}

void	rect(int x, int y, int width, int height)
{
	sfVector2f	pos = {x * game.settings.baseScale.x, y * game.settings.baseScale.y};
	sfVector2f	size = {width * game.settings.baseScale.x, height * game.settings.baseScale.y};

	sfRectangleShape_setPosition(game.ressources.rectangle, pos);
	sfRectangleShape_setSize(game.ressources.rectangle, size);
	sfRenderWindow_drawRectangleShape(game.ressources.window, game.ressources.rectangle, NULL);
}
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

void	text(char *str, int x, int y, bool isUnicode)
{
	sfVector2f	pos = {x * game.settings.baseScale.x, y * game.settings.baseScale.y};

	if (str && sfText_getFont(game.ressources.text)) {
		if (isUnicode)
			sfText_setUnicodeString(game.ressources.text, (sfUint32 *)str);
		else
			sfText_setString(game.ressources.text, str);
		sfText_setPosition(game.ressources.text, pos);
		sfText_setScale(game.ressources.text, game.settings.baseScale);
		sfRenderWindow_drawText(game.ressources.window, game.ressources.text, 0);
	}
}
