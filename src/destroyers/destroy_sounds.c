#include <SFML/Audio.h>
#include <stdio.h>
#include <malloc.h>
#include <logger.h>
#include "utils.h"
#include "structs.h"

void	destroySounds()
{
	for (int i = 0; i < game.resources.musics.length; i++) {
		logMsg(LOGGER_DEBUG, "Destroying music %i", i);
		if (getMusic(i) != NULL)
			sfMusic_destroy(getMusic(i));
	}
	free(game.resources.musics.content);
	for (int i = 0; i < game.resources.sfx.length; i++) {
		logMsg(LOGGER_DEBUG, "Destroying sfx %i", i);
		if (getSoundEffect(i) != NULL)
			sfSoundBuffer_destroy(getSoundEffect(i));
	}
	free(game.resources.sfx.content);
	playSoundEffect(NULL);
}
