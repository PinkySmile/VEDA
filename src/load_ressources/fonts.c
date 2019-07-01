#include <stdlib.h>
#include <stdio.h>
#include <logger.h>
#include "utils.h"
#include "display.h"
#include "structs.h"
#include "configs.h"
#include "functions.h"
#include "concatf.h"

Array	loadFonts()
{
	Array	array = {NULL, 0};
	int	len = 0;
	sfFont	**fonts = NULL;

	for (; fonts_conf[len]; len++);
	logMsg(LOGGER_INFO, "Loading %i fonts", len);
	fonts = malloc(sizeof(*fonts) * len);
	if (!fonts) {
		logMsg(LOGGER_FATAL, "Couldn't allocate %liB of memory", (long)sizeof(*fonts) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = fonts;
	for (int i = 0; fonts_conf[i]; i++) {
		logMsg(LOGGER_INFO, "Loading file %s", fonts_conf[i]);
		fonts[i] = sfFont_createFromFile(fonts_conf[i]);
		if (i == ARIAL) {
			if (!fonts[i]) {
				dispMsg("Loading error.", concatf(ERROR_DEFAULT_FONT, fonts_conf[i]), MB_OK | MB_ICONERROR);
				exit(EXIT_FAILURE);
			} else
				setFont(game.resources.text, fonts[ARIAL]);
		}
		displayLoadingBar(1, MAX_STEPS, i + 1, len, "Loading fonts");
		if (!fonts[i])
			logMsg(LOGGER_ERROR, "Couldn't load file %s", fonts_conf[i]);
	}
	logMsg(LOGGER_INFO, "Fonts loaded !");
	return (array);
}
