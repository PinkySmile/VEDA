#include <lauxlib.h>
#include <string.h>
#include <stdlib.h>
#include "save.h"
#include "utils.h"
#include "structs.h"
#include "loading.h"
#include "creators.h"
#include "discord_rp.h"
#include "battle_lua.h"

void	loadRessources()
{
	game.ressources.rectangle	= createRectangleShape();
	game.ressources.text		= createText();
	game.ressources.fonts		= loadFonts();
	game.ressources.sprites		= loadSprites();
	game.ressources.musics		= loadMusics();
	game.ressources.sfx		= loadSfx();
	game.ressources.languages	= loadLanguages();
	game.ressources.buttons		= loadButtons();
	setVolumes(game.ressources.sfx, game.settings.sfxVolume);
	setVolumes(game.ressources.musics, game.settings.musicVolume);
}

void	initDialogsScript()
{
	game.ressources.dialogLuaScript = luaL_newstate();
	addDependencies(game.ressources.dialogLuaScript);
	if (luaL_dofile(game.ressources.dialogLuaScript, getAbsolutePath("data/dialogs/script.lua"))) {
		printf(
			"%s: An unexpected error occurred when loading %s\n",
			ERROR,
			getAbsolutePath("data/dialogs/script.lua")
		);
		lua_close(game.ressources.dialogLuaScript);
		game.ressources.dialogLuaScript = NULL;
	}
}

void	initGame(bool debug)
{
	Character	player;

	printf("%s: Initializating game\n", INFO);
	memset(&game, 0, sizeof(game));
	srand((long)&game);
	memset(&player, 0, sizeof(player));
	game.debug = debug;
	initDiscordRichPresence();
	game.settings = loadSettings();
	createMainWindow();
	initDialogsScript();
	game.input.bufSize = BUFFER_MAX_SIZE;
	loadRessources();
	sfRenderWindow_setFramerateLimit(game.ressources.window, 60);
}
