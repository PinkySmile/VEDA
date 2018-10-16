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

	if (str && sfText_getFont(game.resources.text)) {
		if (isUnicode)
			sfText_setUnicodeString(game.resources.text, (sfUint32 *)str);
		else
			sfText_setString(game.resources.text, str);
		sfText_setPosition(game.resources.text, pos);
		sfText_setScale(game.resources.text, game.settings.baseScale);
		sfRenderWindow_drawText(game.resources.window, game.resources.text, 0);
	}
}
