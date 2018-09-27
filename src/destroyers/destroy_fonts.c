#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include "structs.h"

void	destroyFonts()
{
	for (int i = 0; i < game.ressources.fonts.length; i++) {
		if (game.debug)
			printf("%s: Destroying font %i\n", INFO, i);
		if (((sfFont **)game.ressources.fonts.content)[i] != NULL)
			sfFont_destroy(((sfFont **)game.ressources.fonts.content)[i]);
	}
	free(game.ressources.fonts.content);
}
