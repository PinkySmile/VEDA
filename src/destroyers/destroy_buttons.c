#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include "structs.h"

void	destroyButtons()
{
	for (int i = 0; game.resources.buttons[i].content; i++) {
		if (game.debug)
			printf("%s: Destroying button %i\n", INFO_BEG, i);
		sfRectangleShape_destroy(game.resources.buttons[i].rect);
	}
	free(game.resources.buttons);
}
