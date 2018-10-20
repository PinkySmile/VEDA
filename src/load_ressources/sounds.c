#include "structs.h"
#include "macros.h"
#include "configs.h"
#include "display.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

sfMusic	*createMusic(Music_config config)
{
	sfMusic	*music = NULL;

	printf("%s: Loading file %s\n", INFO_BEG, config.path);
	music = sfMusic_createFromFile(config.path);
	if (music)
		sfMusic_setLoop(music, config.isRepeated);
	else
		printf("%s: Couldn't load file %s\n", ERROR_BEG, config.path);
	return (music);
}

Array	loadMusics()
{
	Array	array = {NULL, 0};
	int	len = 0;
	sfMusic	**musics = NULL;

	for (; musics_conf[len].path; len++);
	printf("%s: Loading %i musics\n", INFO_BEG, len);
	musics = malloc(sizeof(*musics) * len);
	if (!musics) {
		printf("%s: Couldn't allocate %liB of memory\n", FATAL_BEG, (long)sizeof(*musics) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = musics;
	for (int i = 0; musics_conf[i].path; i++) {
		displayLoadingBar(3, MAX_STEPS, i, len, "Loading musics");
		musics[i] = createMusic(musics_conf[i]);
	}
	printf("%s: Musics loaded !\n", INFO_BEG);
	return (array);
}

sfSoundBuffer	*createSoundBuffer(Music_config config)
{
	sfSoundBuffer	*buffer = NULL;

	printf("%s: Loading file %s\n", INFO_BEG, config.path);
	buffer = sfSoundBuffer_createFromFile(config.path);
	if (!buffer)
		printf("%s: Couldn't load file %s\n", ERROR_BEG, config.path);
	return (buffer);
}

Array	loadSfx()
{
	Array		array = {NULL, 0};
	int		len = 0;
	sfSoundBuffer	**sfx = NULL;

	for (; sfx_conf[len].path; len++);
	printf("%s: Loading %i sfx sounds\n", INFO_BEG, len);
	sfx = malloc(sizeof(*sfx) * len);
	if (!sfx) {
		printf("%s: Couldn't allocate %liB of memory\n", FATAL_BEG, (long)sizeof(*sfx) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = sfx;
	for (int i = 0; sfx_conf[i].path; i++) {
		displayLoadingBar(4, MAX_STEPS, i, len, "Loading sound effects");
		sfx[i] = createSoundBuffer(sfx_conf[i]);
	}
	printf("%s: Sounds loaded !\n", INFO_BEG);
	return (array);
}
