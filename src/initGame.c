#include "structs.h"
#include "functions.h"
#include "macros.h"
#include "concatf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#ifdef __MINGW32__
#include <windows.h>
#endif

void	displayLoadingBar(game_t *game, int step, int maxSteps, int file, int maxFiles, char *status)
{
	sfVector2f	pos2 = {100, 250};
	sfVector2f	size2 = {440 * step / maxSteps, 50};
	sfVector2f	pos = {100, 350};
	sfVector2f	size = {440 * file / maxFiles, 50};
	char		*nbr = concatf("%i/%i", file, maxFiles);

	status = concatf("%s (%i/%i)", status, step, maxSteps);
	if (!nbr || !status) {
		free(nbr);
		free(status);
		printf("%s: Couldn't create loading screen text\n", FATAL);
		exit(EXIT_FAILURE);
	}
	if (game->text) {
		sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
		sfText_setCharacterSize(game->text, 15);
	}
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){150, 150, 150, 255});
	sfRectangleShape_setPosition(game->rectangle, pos);
	sfRectangleShape_setSize(game->rectangle, size);
	sfRenderWindow_clear(game->window, (sfColor){0, 0, 0, 255});
	rect(game, pos.x - 5, pos.y - 5, 450, 60);
	rect(game, pos2.x - 5, pos2.y - 5, 450, 60);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 0, 0, 255});
	rect(game, pos.x, pos.y, 440, 50);
	rect(game, pos2.x, pos2.y, 440, 50);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 0, 255, 255});
	rect(game, pos.x, pos.y, size.x, size.y);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 255, 0, 255});
	rect(game, pos2.x, pos2.y, size2.x, size2.y);
	text(status, game, 320 - strlen(status) / 2 * 6, 310, false);
	text(nbr, game, 320 - strlen(nbr) / 2 * 7, 410, false);
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
		printf("[ERROR]: data/version.txt: %s\n", strerror(errno));
		close(fd);
		version = strdup("?.?.?.?");
		if (!version)
			exit(EXIT_FAILURE);
		return (version);
	} else
		memset(version, 0, 10);
	read(fd, version, 9);
	version[9] = 0;
	close(fd);
	return (version);
}

void	initGame(game_t *game)
{
	char		*title = concat("VEDA version ", getVersion(), false, true);
	const sfUint8	*icon = NULL;
	sfImage		*image = sfImage_createFromFile("data/icon/icon.png");
	sfVideoMode	mode = {640, 480, 32};
	sfWindowStyle	style;
	Character	player;

	memset(game, 0, sizeof(*game));
	memset(&player, 0, sizeof(player));
	game->settings = loadSettings();
	if (game->settings.windowMode == FULLSCREEN) {
		style = sfFullscreen;
		mode = sfVideoMode_getDesktopMode();
	} else if (game->settings.windowMode == BORDERLESS_WINDOW) {
		style = sfNone;
		mode = sfVideoMode_getDesktopMode();
	} else {
		style = sfTitlebar | sfClose;
		mode.width = game->settings.windowSize.x;
		mode.height = game->settings.windowSize.y;
	}
	game->baseScale.x = (float)mode.width / 640.0;
	game->baseScale.y = (float)mode.height / 480.0;
	if (image)
		icon = sfImage_getPixelsPtr(image);
	else
		printf("[ERROR]: Couldn't load icon image\n");
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL);
		#ifdef __MINGW32__
		MessageBox(NULL, "Couldn't create window title", "Window error", 0);
		#endif
		exit(EXIT_FAILURE);
	}
	game->window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game->window) {
		printf("%s: Couldn't create window\n", FATAL);
		#ifdef __MINGW32__
		MessageBox(NULL, "Couldn't create window object", "Window error", 0);
		#endif
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
	if (!game->text) {
		printf("%s: Couldn't create text object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game->icon.image = image;
	if (image)
		game->icon.texture = sfTexture_createFromImage(image, NULL);
	game->icon.sprite = sfSprite_create();
	if (game->icon.sprite && game->icon.texture)
		sfSprite_setTexture(game->icon.sprite, game->icon.texture, sfTrue);
	memset(&game->characters, 0, sizeof(game->characters));/*
	game->characters.content = malloc(sizeof(Character));
	if (!game->characters.content) {
		printf("%s: Couldn't create player object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game->characters.length = 1;
	game->selected = -1;
	player.movement.animationClock = sfClock_create();
	player.movement.stateClock = sfClock_create();
	player.stats.energyRegenClock = sfClock_create();
	player.stats.energyRegen = 1;
	player.stats.energyUsedBySprint = 1;
	player.stats.sprintSpeed = 2;
	player.stats.timeBeforeEnergyUse = 1;
	player.stats.life = 332;
	player.stats.lifeMax = 45;
	player.stats.energy = 1332;
	player.stats.maxEnergy = 145;
	player.movement.canMove = true;
	player.isPlayer = true;
	player.texture = 0;
	strcpy(player.name, game->settings.playerName);
	for (int i = 0; i < DAMAGES_TYPE_NB; i++)
		player.damageClock[i] = sfClock_create();
	((Character *)game->characters.content)[0] = player;*/
	memset(game->buffer, 0, BUFFER_MAX_SIZE * sizeof(*game->buffer));
	game->bufSize = BUFFER_MAX_SIZE;
	game->fonts = loadFonts(game);
	game->sprites = loadSprites(game);
	game->musics = loadMusics(game);
	setVolumes(game->musics, game->settings.musicVolume);
	game->sfx = loadSfx(game);
	setVolumes(game->sfx, game->settings.sfxVolume);
	game->languages = loadLanguages(game);
	game->buttons = loadButtons(game);
	sfRenderWindow_setFramerateLimit(game->window, 60);
	free(title);
}
