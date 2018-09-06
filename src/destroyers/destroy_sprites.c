#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>

void	destroySprites()
{
	for (int i = 0; i < game.ressources.sprites.length; i++) {
		if (game.debug)
			printf("%s: Destroying sprite %i\n", INFO, i);
		if (((Sprite *)game.ressources.sprites.content)[i].sprite != NULL)
			sfSprite_destroy(((Sprite *)game.ressources.sprites.content)[i].sprite);
		if (((Sprite *)game.ressources.sprites.content)[i].texture != NULL)
			sfTexture_destroy(((Sprite *)game.ressources.sprites.content)[i].texture);
	}
	free(game.ressources.sprites.content);
}