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

char	*getVersion()
{
	int	fd = open("data/version.txt", O_RDONLY);
	char	*version = malloc(10);

	printf("%s: Loading version string\n", INFO);
	if (!version)
		exit(EXIT_FAILURE);
	if (fd < 0) {
		free(version);
		printf("[ERROR]: data/version.txt: %s\n", strerror(errno));
		close(fd);
		version = strdup("?.?.?.?");
		if (!version)
			exit(EXIT_FAILURE);
		return (version);
	}
	version[read(fd, version, 9)] = 0;
	close(fd);
	return (version);
}

void	initGame(bool debug)
{
	char		*title;
	const sfUint8	*icon = NULL;
	sfImage		*image;
	sfVideoMode	mode = {640, 480, 32};
	sfWindowStyle	style;
	Character	player;

	printf("%s: Initializating game\n", INFO);
	memset(&game, 0, sizeof(game));
	srand((long)&game);
	memset(&player, 0, sizeof(player));
	game.debug = debug;
	printf("%s: Init discord rich presence\n", INFO);
	initDiscordRichPresence();
	title = concat("VEDA version ", getVersion(), false, true);
	if (!title)
		exit(EXIT_FAILURE);
	image = sfImage_createFromFile("data/icon/icon.png");
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
	game.ressources.window = createRenderWindow(mode, title, style, NULL, false);
	if (!game.ressources.window)
		exit(EXIT_FAILURE);
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
