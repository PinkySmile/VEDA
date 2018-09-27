#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include "structs.h"

void	destroyButtons()
{
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		if (game.debug)
			printf("%s: Destroying button %i\n", INFO, i);
		sfRectangleShape_destroy(game.ressources.buttons[i].rect);
	}
	free(game.ressources.buttons);
}
