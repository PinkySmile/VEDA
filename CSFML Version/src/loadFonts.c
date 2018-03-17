#include "structs.h"
#include "fonts_conf.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

Array	loadFonts(game_t *game)
{
	Array	array = {NULL, 0};
	int	len = 0;
	sfFont	**fonts = NULL;

	for (; fonts_conf[len]; len++);
	printf("%s: Loading %i fonts\n", INFO, len);
	fonts = malloc(sizeof(*fonts) * len);
	if (!fonts) {
		printf("%s: Couldn't allocate %liB of memory\n", FATAL, sizeof(*fonts) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = fonts;
	for (int i = 0; fonts_conf[i]; i++) {
		printf("%s: Loading file %s\n", INFO, fonts_conf[i]);
		fonts[i] = sfFont_createFromFile(fonts_conf[i]);
		if (i == ARIAL)
			setFont(game->text, fonts[ARIAL]);
		displayLoadingBar(game, 1, MAX_STEPS, i + 1, len, "Loading fonts");
		if (!fonts[i])
			printf("%s: Couldn't load file %s\n", ERROR, fonts_conf[i]);
	}
	printf("%s: Fonts loaded !\n", INFO);
	return (array);
}