#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include "structs.h"

void	destroyFonts()
{
	for (int i = 0; i < game.resources.fonts.length; i++) {
		if (game.debug)
			printf("%s: Destroying font %i\n", INFO_BEG, i);
		if (((sfFont **)game.resources.fonts.content)[i] != NULL)
			sfFont_destroy(((sfFont **)game.resources.fonts.content)[i]);
	}
	free(game.resources.fonts.content);
}
