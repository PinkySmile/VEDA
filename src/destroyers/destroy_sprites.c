#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include <logger.h>
#include "structs.h"
#include "macros.h"

void	destroySprites()
{
	for (int i = 0; i < game.resources.sprites.length; i++) {
		logMsg(LOGGER_DEBUG, "Destroying sprite %i", i);
		if (getSprite(i)->sprite != NULL)
			sfSprite_destroy(getSprite(i)->sprite);
		if (getSprite(i)->texture != NULL)
			sfTexture_destroy(getSprite(i)->texture);
	}
	free(game.resources.sprites.content);
}