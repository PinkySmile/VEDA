#include "structs.h"
#include "macros.h"
#include "sounds_conf.h"
#include <stdio.h>
#include <stdlib.h>

sfMusic	*createMusic(Music_config config)
{
	sfMusic	*music = NULL;

	printf("%s: Loading file %s\n", INFO, config.path);
	music = sfMusic_createFromFile(config.path);
	if (music)
		sfMusic_setLoop(music, config.isRepeated);
	else
		printf("%s: Couldn't load file %s\n", ERROR, config.path);
	return (music);
}

Array	loadMusics()
{
	Array	array = {NULL, 0};
	int	len = 0;
	sfMusic	**musics = NULL;

	for (; musics_conf[len].path; len++);
	printf("%s: Loading %i musics\n", INFO, len);
	musics = malloc(sizeof(*musics) * len);
	if (!musics) {
		printf("%s: Couldn't allocate %liB of memory\n", FATAL, sizeof(*musics) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = musics;
	for (int i = 0; musics_conf[i].path; i++)
		musics[i] = createMusic(musics_conf[i]);
	printf("%s: Musics loaded !\n", INFO);
	return (array);
}

Array	loadSfx()
{
	Array	array = {NULL, 0};
	int	len = 0;
	sfMusic	**sfx = NULL;

	for (; sfx_conf[len].path; len++);
	printf("%s: Loading %i sfx sounds\n", INFO, len);
	sfx = malloc(sizeof(*sfx) * len);
	if (!sfx) {
		printf("%s: Couldn't allocate %liB of memory\n", FATAL, sizeof(*sfx) * len);
		exit(EXIT_FAILURE);
	}
	array.length = len;
	array.content = sfx;
	for (int i = 0; sfx_conf[i].path; i++)
		sfx[i] = createMusic(sfx_conf[i]);
	printf("%s: Sounds loaded !\n", INFO);
	return (array);
}
