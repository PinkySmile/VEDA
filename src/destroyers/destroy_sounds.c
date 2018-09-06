#include <SFML/Audio.h>
#include <stdio.h>
#include <malloc.h>

void	destroySounds()
{

	for (int i = 0; i < game.ressources.musics.length; i++) {
		if (game.debug)
			printf("%s: Destroying music %i\n", INFO, i);
		if (((sfMusic **)game.ressources.musics.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game.ressources.musics.content)[i]);
	}
	free(game.ressources.musics.content);
	for (int i = 0; i < game.ressources.sfx.length; i++) {
		if (game.debug)
			printf("%s: Destroying sfx %i\n", INFO, i);
		if (((sfMusic **)game.ressources.sfx.content)[i] != NULL)
			sfMusic_destroy(((sfMusic **)game.ressources.sfx.content)[i]);
	}
	free(game.ressources.sfx.content);
}
