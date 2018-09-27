#include <SFML/Graphics.h>
#include <stdbool.h>
#include "globals.h"

void	setFont(sfText *text, sfFont *font)
{
	if (font && text)
		sfText_setFont(text, font);
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
