#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include <logger.h>
#include "structs.h"

void	destroyButtons()
{
	for (int i = 0; game.resources.buttons[i].content; i++) {
		logMsg(LOGGER_DEBUG, "Destroying button %i", i);
		sfRectangleShape_destroy(game.resources.buttons[i].rect);
	}
	free(game.resources.buttons);
}
