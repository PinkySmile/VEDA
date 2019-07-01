#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include <logger.h>
#include "structs.h"

void	destroyFonts()
{
	for (int i = 0; i < game.resources.fonts.length; i++) {
		logMsg(LOGGER_DEBUG, "Destroying font %i", i);
		if (((sfFont **)game.resources.fonts.content)[i] != NULL)
			sfFont_destroy(((sfFont **)game.resources.fonts.content)[i]);
	}
	free(game.resources.fonts.content);
}
