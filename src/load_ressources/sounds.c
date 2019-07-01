#include "structs.h"
#include "macros.h"
#include "configs.h"
#include "display.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <logger.h>

sfMusic	*createMusic(Music_config config)
{
	sfMusic	*music = NULL;

	logMsg(LOGGER_DEBUG, "Loading file %s", config.path);
	music = sfMusic_createFromFile(config.path);
	if (music)
		sfMusic_setLoop(music, config.isRepeated);
	else
		logMsg(LOGGER_ERROR, "Couldn't load file %s", config.path);
	return (music);
}

Array	loadMusics()
{
	Array	array = {NULL, 0};
	int	len = 0;
	sfMusic	**musics = NULL;

	for (; musics_conf[len].path; len++);
	logMsg(LOGGER_INFO, "Loading %i musics", len);
	musics = malloc(sizeof(*musics) * len);
	if (!musics) {
		logMsg(LOGGER_FATAL, "Couldn't allocate %liB of memory", (long)sizeof(*musics) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = musics;
	for (int i = 0; musics_conf[i].path; i++) {
		displayLoadingBar(3, MAX_STEPS, i, len, "Loading musics");
		musics[i] = createMusic(musics_conf[i]);
	}
	logMsg(LOGGER_INFO, "Musics loaded !");
	return (array);
}

sfSoundBuffer	*createSoundBuffer(Music_config config)
{
	sfSoundBuffer	*buffer = NULL;

	logMsg(LOGGER_INFO, "Loading file %s", config.path);
	buffer = sfSoundBuffer_createFromFile(config.path);
	if (!buffer)
		logMsg(LOGGER_ERROR, "Couldn't load file %s", config.path);
	return (buffer);
}

Array	loadSfx()
{
	Array		array = {NULL, 0};
	int		len = 0;
	sfSoundBuffer	**sfx = NULL;

	for (; sfx_conf[len].path; len++);
	logMsg(LOGGER_INFO, "Loading %i sfx sounds", len);
	sfx = malloc(sizeof(*sfx) * len);
	if (!sfx) {
		logMsg(LOGGER_FATAL, "Couldn't allocate %liB of memory", (long)sizeof(*sfx) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = sfx;
	for (int i = 0; sfx_conf[i].path; i++) {
		displayLoadingBar(4, MAX_STEPS, i, len, "Loading sound effects");
		sfx[i] = createSoundBuffer(sfx_conf[i]);
	}
	logMsg(LOGGER_INFO, "Sounds loaded !");
	return (array);
}
