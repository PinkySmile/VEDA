#include <SFML/Audio.h>
#include <stdio.h>
#include <malloc.h>
#include "utils.h"
#include "structs.h"

void	destroySounds()
{

	for (int i = 0; i < game.resources.musics.length; i++) {
		if (game.debug)
			printf("%s: Destroying music %i\n", INFO_BEG, i);
		if (getMusic(i) != NULL)
			sfMusic_destroy(getMusic(i));
	}
	free(game.resources.musics.content);
	for (int i = 0; i < game.resources.sfx.length; i++) {
		if (game.debug)
			printf("%s: Destroying sfx %i\n", INFO_BEG, i);
		if (getSoundEffect(i) != NULL)
			sfSoundBuffer_destroy(getSoundEffect(i));
	}
	free(game.resources.sfx.content);
	playSoundEffect(NULL);
}
