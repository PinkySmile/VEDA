#include <SFML/Graphics.h>
#include "structs.h"

void	destroySfmlObjects()
{
	sfText_destroy(game.resources.text);
	sfImage_destroy(game.resources.icon.image);
	sfSprite_destroy(game.resources.icon.sprite);
	sfTexture_destroy(game.resources.icon.texture);
	sfRenderWindow_destroy(game.resources.window);
	sfRectangleShape_destroy(game.resources.rectangle);
}
