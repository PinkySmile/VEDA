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
	game.resources.rectangle	= createRectangleShape();
	game.resources.text		= createText();
	game.resources.fonts		= loadFonts();
	game.resources.sprites		= loadSprites();
	game.resources.musics		= loadMusics();
	game.resources.sfx		= loadSfx();
	game.resources.languages	= loadLanguages();
	game.resources.buttons		= loadButtons();
	setVolumes(game.resources.musics, game.settings.musicVolume);
}

void	initDialogsScript()
{
	game.resources.dialogLuaScript = luaL_newstate();
	addDependencies(game.resources.dialogLuaScript);
	if (luaL_dofile(game.resources.dialogLuaScript, getAbsolutePath("data/dialogs/script.lua"))) {
		printf(
			"%s: An unexpected error occurred when loading %s\n",
			ERROR_BEG,
			getAbsolutePath("data/dialogs/script.lua")
		);
		lua_close(game.resources.dialogLuaScript);
		game.resources.dialogLuaScript = NULL;
	}
}

void	initGame(bool debug)
{
	Character	player;

	printf("%s: Initializating game\n", INFO_BEG);
	memset(&game, 0, sizeof(game));
	srand((long)&game);
	memset(&player, 0, sizeof(player));
	game.debug = debug;
	initDiscordRichPresence();
	game.settings = loadSettings();
	game.resources.window = createMainWindow();
	initDialogsScript();
	game.input.bufSize = BUFFER_MAX_SIZE;
	loadRessources();
	sfRenderWindow_setFramerateLimit(game.resources.window, 60);
}
