#include <SFML/Graphics.h>
#include "game_struct.h"

void	rect(int x, int y, int width, int height)
{
	sfVector2f	pos = {x * game.settings.baseScale.x, y * game.settings.baseScale.y};
	sfVector2f	size = {width * game.settings.baseScale.x, height * game.settings.baseScale.y};

	sfRectangleShape_setPosition(game.ressources.rectangle, pos);
	sfRectangleShape_setSize(game.ressources.rectangle, size);
	sfRenderWindow_drawRectangleShape(game.ressources.window, game.ressources.rectangle, NULL);
}