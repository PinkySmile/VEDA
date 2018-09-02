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

void	displayLoadingBar(int step, int maxSteps, int file, int maxFiles, char *status)
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
	if (game.ressources.text) {
		sfText_setColor(game.ressources.text, (sfColor){255, 255, 255, 255});
		sfText_setCharacterSize(game.ressources.text, 15);
	}
	sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){150, 150, 150, 255});
	sfRectangleShape_setPosition(game.ressources.rectangle, pos);
	sfRectangleShape_setSize(game.ressources.rectangle, size);
	sfRenderWindow_clear(game.ressources.window, (sfColor){0, 0, 0, 255});
	rect(pos.x - 5, pos.y - 5, 450, 60);
	rect(pos2.x - 5, pos2.y - 5, 450, 60);
	sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){0, 0, 0, 255});
	rect(pos.x, pos.y, 440, 50);
	rect(pos2.x, pos2.y, 440, 50);
	sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){0, 0, 255, 255});
	rect(pos.x, pos.y, size.x, size.y);
	sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){0, 255, 0, 255});
	rect(pos2.x, pos2.y, size2.x, size2.y);
	text(status, 320 - strlen(status) / 2 * 6, 310, false);
	text(nbr, 320 - strlen(nbr) / 2 * 7, 410, false);
	if (game.ressources.sprites.content && ((Sprite *)game.ressources.sprites.content)[ICON].sprite)
		image(((Sprite *)game.ressources.sprites.content)[ICON].sprite, 256, 100, 128, 128);
	else if (game.ressources.icon.sprite)
		image(game.ressources.icon.sprite, 256, 100, 128, 128);
	sfRenderWindow_display(game.ressources.window);
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

void	initGame()
{
	char		*title = concat("VEDA version ", getVersion(), false, true);
	const sfUint8	*icon = NULL;
	sfImage		*image = sfImage_createFromFile("data/icon/icon.png");
	sfVideoMode	mode = {640, 480, 32};
	sfWindowStyle	style;
	Character	player;

	memset(&game, 0, sizeof(game));
	memset(&player, 0, sizeof(player));
	game.settings = loadSettings();
	if (game.settings.windowMode == FULLSCREEN) {
		style = sfFullscreen;
		mode = sfVideoMode_getDesktopMode();
	} else if (game.settings.windowMode == BORDERLESS_WINDOW) {
		style = sfNone;
		mode = sfVideoMode_getDesktopMode();
	} else {
		style = sfTitlebar | sfClose;
		mode.width = game.settings.windowSize.x;
		mode.height = game.settings.windowSize.y;
	}
	game.settings.baseScale.x = (float)mode.width / 640.0;
	game.settings.baseScale.y = (float)mode.height / 480.0;
	if (image)
		icon = sfImage_getPixelsPtr(image);
	else
		printf("[ERROR]: Couldn't load icon image\n");
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL);
		dispMsg("Window error", "Couldn't create window title", 0);
		exit(EXIT_FAILURE);
	}
	game.ressources.window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game.ressources.window) {
		printf("%s: Couldn't create window\n", FATAL);
		dispMsg("Window error", "Couldn't create window object", 0);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game.ressources.window, 32, 32, icon);
	game.ressources.rectangle = sfRectangleShape_create();
	if (!game.ressources.rectangle) {
		printf("%s: Couldn't create rectangle object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game.ressources.text = sfText_create();
	if (!game.ressources.text) {
		printf("%s: Couldn't create text object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game.ressources.icon.image = image;
	if (image)
		game.ressources.icon.texture = sfTexture_createFromImage(image, NULL);
	game.ressources.icon.sprite = sfSprite_create();
	if (game.ressources.icon.sprite && game.ressources.icon.texture)
		sfSprite_setTexture(game.ressources.icon.sprite, game.ressources.icon.texture, sfTrue);
	memset(&game.state.characters, 0, sizeof(game.state.characters));
	game.ressources.dialogLuaScript = luaL_newstate();
	addDependencies(game.ressources.dialogLuaScript);
	if (luaL_dofile(game.ressources.dialogLuaScript, "data/dialogs/script.lua")) {
		printf("%s: An unexpected error occurred when loading data/dialogs/script.lua\n", ERROR);
		lua_close(game.ressources.dialogLuaScript);
		game.ressources.dialogLuaScript = NULL;
	}/*
	game.state.characters.content = malloc(sizeof(Character));
	if (!game.state.characters.content) {
		printf("%s: Couldn't create player object\n", FATAL);
		exit(EXIT_FAILURE);
	}
	game.state.characters.length = 1;
	game.state.menuSelected = -1;
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
	strcpy(player.name, game.settings.playerName);
	for (int i = 0; i < DAMAGES_TYPE_NB; i++)
		player.damageClock[i] = sfClock_create();
	((Character *)game.state.characters.content)[0] = player;*/
	memset(game.input.buffer, 0, BUFFER_MAX_SIZE * sizeof(*game.input.buffer));
	game.input.bufSize = BUFFER_MAX_SIZE;
	game.ressources.fonts = loadFonts();
	game.ressources.sprites = loadSprites();
	game.ressources.musics = loadMusics();
	setVolumes(game.ressources.musics, game.settings.musicVolume);
	game.ressources.sfx = loadSfx();
	setVolumes(game.ressources.sfx, game.settings.sfxVolume);
	game.ressources.languages = loadLanguages();
	game.ressources.buttons = loadButtons();
	sfRenderWindow_setFramerateLimit(game.ressources.window, 60);
	free(title);
}
