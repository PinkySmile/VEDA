#include <SFML/Graphics.h>
#include "globals.h"

void	rect(int x, int y, int width, int height)
{
	sfVector2f	pos = {x * game.settings.baseScale.x, y * game.settings.baseScale.y};
	sfVector2f	size = {width * game.settings.baseScale.x, height * game.settings.baseScale.y};

	sfRectangleShape_setPosition(game.resources.rectangle, pos);
	sfRectangleShape_setSize(game.resources.rectangle, size);
	sfRenderWindow_drawRectangleShape(game.resources.window, game.resources.rectangle, NULL);
}