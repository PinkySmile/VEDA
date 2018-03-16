#include "structs.h"
#include "functions.h"
#include "macros.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

char	*getVersion()
{
	int	fd = open("data/version.txt", O_RDONLY);
	char	*version = malloc(10);

	printf("%s: Loading version string\n", INFO);
	if (fd < 0 || !version) {
		free(version);
		printf("%s: data/version.txt: %s\n", ERROR, strerror(errno));
		close(fd);
		return (strdup("?.?.?.?"));
	}
	read(fd, version, 9);
	version[9] = 0;
	close(fd);
	return (version);
}

void	initGame(game_t *game)
{
	char		*title = concat("VEDA version ", getVersion(), false, true);
	const sfUint8	*icon = NULL;
	sfImage		*image = sfImage_createFromFile("data/misc/icon.png");
	sfVideoMode	mode = {640, 480, 32};
	sfWindowStyle	style;

	memset(game, 0, sizeof(*game));
	game->settings = loadSettings();
	if (game->settings.windowMode == FULLSCREEN)
		style = sfFullscreen;
	else if (game->settings.windowMode == BORDERLESS_WINDOW) {
		style = sfNone;
		mode = sfVideoMode_getDesktopMode();
	} else
		style = sfDefaultStyle;
	if (image)
		icon = sfImage_getPixelsPtr(image);
	else
		printf("%s: Couldn't load icon image\n", ERROR);
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game->sprites = loadSprites();
	game->musics = loadMusics();
	game->sfx = loadSfx();
	game->window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game->window) {
		printf("%s: Couldn't create window\n", FATAL);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game->window, 32, 32, icon);
	free(title);
}
