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

void	displayLoadingBar(game_t *game, float step, float maxSteps, float file, float maxFiles, char *status)
{
	sfVector2f	pos2 = {100 * game->baseScale.x, 250 * game->baseScale.y};
	sfVector2f	size2 = {(440 * step / maxSteps) * game->baseScale.x, 50 * game->baseScale.y};
	sfVector2f	pos = {100 * game->baseScale.x, 350 * game->baseScale.y};
	sfVector2f	size = {(440 * file / maxFiles) * game->baseScale.x, 50 * game->baseScale.y};
	char		*nbr = concat(int_to_str((int)file), "/", true, false);
	
	status = concat(status, " (", false, false);
	status = concat(status, int_to_str((int)step), true, true);
	status = concat(status, "/", true, false);
	status = concat(status, int_to_str((int)maxSteps), true, true);
	status = concat(status, ")", true, false);
	nbr = concat(nbr, int_to_str((int)maxFiles), true, true);
	if (!nbr || !status) {
		free(nbr);
		free(status);
		printf("%s: Couldn't create loading screen text\n", FATAL);
		exit(EXIT_FAILURE);
	}
	if (game->text) {
		sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
		sfText_setCharacterSize(game->text, 15 * game->baseScale.x);
	}
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){150, 150, 150, 255});
	sfRectangleShape_setPosition(game->rectangle, pos);
	sfRectangleShape_setSize(game->rectangle, size);
	sfRenderWindow_clear(game->window, (sfColor){0, 0, 0, 255});
	rect(game, pos.x - 5 * game->baseScale.x, pos.y - 5 * game->baseScale.y, 450 * game->baseScale.x, 60 * game->baseScale.y);
	rect(game, pos2.x - 5 * game->baseScale.x, pos2.y - 5 * game->baseScale.y, 450 * game->baseScale.x, 60 * game->baseScale.y);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 0, 0, 255});
	rect(game, pos.x, pos.y, 440 * game->baseScale.x, 50 * game->baseScale.y);
	rect(game, pos2.x, pos2.y, 440 * game->baseScale.x, 50 * game->baseScale.y);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 0, 255, 255});
	rect(game, pos.x, pos.y, size.x, size.y);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 255, 0, 255});
	rect(game, pos2.x, pos2.y, size2.x, size2.y);
	text(status, game, (320 - (strlen(status) / 2) * 6) * game->baseScale.x, 320 * game->baseScale.y);
	text(nbr, game, (320 - strlen(nbr)/2 * 7) * game->baseScale.x, 420 * game->baseScale.y);
	image(game, game->icon.sprite, 256, 100, 128, 128);
	sfRenderWindow_display(game->window);
	free(nbr);
	free(status);
}

char	*getVersion()
{
	int	fd = open("data/version.txt", O_RDONLY);
	char	*version = malloc(10);

	printf("%s: Loading version string\n", INFO);
	if (fd < 0 || !version) {
		free(version);
		printf("%s: data/version.txt: %s\n", ERROR, strerror(errno));
		close(fd);
		version = strdup("?.?.?.?");
		if (!version)
			exit(EXIT_FAILURE);
		return (version);
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
	if (game->settings.windowMode == FULLSCREEN) {
		style = sfFullscreen;
		mode = sfVideoMode_getDesktopMode();
	} else if (game->settings.windowMode == BORDERLESS_WINDOW) {
		style = sfNone;
		mode = sfVideoMode_getDesktopMode();
	} else
		style = sfDefaultStyle;
	game->baseScale.x = (float)mode.width / 640.0;
	game->baseScale.y = (float)mode.height / 480.0;
	if (image)
		icon = sfImage_getPixelsPtr(image);
	else
		printf("%s: Couldn't load icon image\n", ERROR);
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game->window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game->window) {
		printf("%s: Couldn't create window\n", FATAL);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game->window, 32, 32, icon);
	game->rectangle = sfRectangleShape_create();
	if (!game->rectangle) {
		printf("%s: Couldn't create rectangle object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game->text = sfText_create();
	if (!game->rectangle) {
		printf("%s: Couldn't create text object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game->icon.image = image;
	if (image)
		game->icon.texture = sfTexture_createFromImage(image, NULL);
	game->icon.sprite = sfSprite_create();
	if (game->icon.sprite && game->icon.texture)
		sfSprite_setTexture(game->icon.sprite, game->icon.texture, sfTrue);
	game->fonts = loadFonts(game);
	game->sprites = loadSprites(game);
	game->musics = loadMusics(game);
	game->sfx = loadSfx(game);
	game->buttons = loadButtons(game);
	game->languages = loadLanguages(game);
	free(title);
}
