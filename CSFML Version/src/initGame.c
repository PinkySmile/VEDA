#include "structs.h"
#include "functions.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>

char	*getVersion()
{
	int	fd = open("data/version.txt", O_RDONLY);
	char	*version = malloc(10);

	printf("[INFO]:Loading version string\n");
	if (fd < 0 || !version) {
		free(version);
		printf("[ERROR]:data/version.txt: %s\n", strerror(errno));
		close(fd);
		return (strdup("?.?.?.?"));
	}
	read(fd, version, 9);
	version[9] = 0;
	close(fd);
	return (version);
}

sfUint8	*getIcon()
{
	int		fd 	= open("data/icon", O_RDONLY);
	sfUint8		*array 	= malloc(2048);
	sfUint16	*result = malloc(4096);

	printf("[INFO]:Loading icon\n");
	if (fd < 0 || !array) {
		free(array);
		printf("[ERROR]:data/icon: %s\n", strerror(errno));
		close(fd);
		return (NULL);
	}
	read(fd, array, 2048);
	for (int i = 0; i < 2048; i++) {
		result[i] = array[i];
		if (result[i] == 255)
			result[i] = 0;
	}
	close(fd);
	return ((sfUint8 *)result);
}

void	initGame(game_t *game)
{
	char	*title = concat("VEDA version ", getVersion(), false, true);
	sfUint8	*icon = getIcon();

	if (!title)
		exit(1);
	memset(game, 0, sizeof(*game));
	game->window = sfRenderWindow_create((sfVideoMode){640, 480, 32}, title, sfResize | sfClose, NULL);
	if (icon)
		sfRenderWindow_setIcon(game->window, 32, 32, icon);
	free(title);
	if (!game->window)
		exit(1);
	game->sprites = loadSprites();
	game->musics = loadMusics();
	game->sfx = loadSfx();
}