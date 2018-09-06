#include <SFML/Graphics.h>

void	destroySfmlObjects()
{
	sfText_destroy(game.ressources.text);
	sfImage_destroy(game.ressources.icon.image);
	sfSprite_destroy(game.ressources.icon.sprite);
	sfTexture_destroy(game.ressources.icon.texture);
	sfRenderWindow_destroy(game.ressources.window);
	sfRectangleShape_destroy(game.ressources.rectangle);
}
