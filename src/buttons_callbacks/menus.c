#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "save.h"
#include "utils.h"
#include "loading.h"
#include "structs.h"
#include "concatf.h"
#include "functions.h"
#include "discord_rp.h"

void	backOnTitleScreen(int buttonID)
{
	(void)buttonID;
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	for (int i = 0; i < 3; i++) {
		game.resources.buttons[i].active = true;
		game.resources.buttons[i].displayed = true;
	}
	for (int i = 0; i < game.resources.musics.length; i++)
		if (i != MAIN_MENU_MUSIC && getMusic(i) && sfMusic_getStatus(getMusic(i)) == sfPlaying)
			sfMusic_stop(((sfMusic **)game.resources.musics.content)[i]);
	if (game.state.battle_infos.music && sfMusic_getStatus(game.state.battle_infos.music) == sfPlaying)
		sfMusic_stop(game.state.battle_infos.music);
	updateDiscordPresence("Main Menu", "In Main Menu", 0, false, "icon", 0, "VEDA", 0);
	game.state.menu = 0;
}

void	playButton(int buttonID)
{
	char	*buffer;

	(void)buttonID;
	free(game.state.loadedMap.objects);
	game.state.loadedMap.objects = NULL;
	loadGame();
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	if (!game.state.loadedMap.objects || !game.state.characters.content) {
		loadLevel("data/levels/test");
		game.state.loadedMap.path = strdup("data/levels/test");
	}
	if (strcmp((char *)getPlayer(game.state.characters.content, game.state.characters.length)->name, "") == 0) {
		updateDiscordPresence("Main Menu", "Choosing name", 0, false, "icon", 0, "VEDA", 0);
		game.state.menu = 6;
		game.input.bufPos = 0;
		game.input.bufSize = 32;
		game.resources.buttons[9].active = true;
		game.resources.buttons[9].displayed = true;
		game.resources.buttons[14].active = true;
		game.resources.buttons[14].displayed = true;
		memset(game.input.buffer, 0, sizeof(*game.input.buffer) * 17);
	} else {
		buffer = concatf("Playing as \"%s\"", getPlayer(game.state.characters.content, game.state.characters.length)->name);
		updateDiscordPresence("In Game", buffer, 0, false, "icon", 0, "VEDA", 0);
		free(buffer);
		game.state.menu = 1;
	}
	if (getMusic(MAIN_MENU_MUSIC) && sfMusic_getStatus(getMusic(MAIN_MENU_MUSIC)) == sfPlaying)
		sfMusic_stop(getMusic(MAIN_MENU_MUSIC));
}

void	changePlayerName(int buttonID)
{
	Character	*player = getPlayer(game.state.characters.content, game.state.characters.length);
	char		*buffer;

	(void)buttonID;
	memset(player->name, 0, 33);
	for (int i = 0; game.input.buffer[i]; i++)
		player->name[i] = game.input.buffer[i] % 255;
	game.state.menu = 1;
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	buffer = concatf("Playing as \"%s\"", player->name);
	updateDiscordPresence("In Game", buffer, 0, false, "icon", 0, "VEDA", 0);
	free(buffer);
}

void	changeKey(int buttonID)
{
	if (game.state.menuSelected >= 0)
		game.resources.buttons[game.state.menuSelected].content = getKeyString(game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x]);
	game.state.menuSelected = buttonID;
	if (game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x] > 204 && game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x] != (unsigned char)-1)
		free(game.resources.buttons[game.state.menuSelected].content);
	game.resources.buttons[game.state.menuSelected].content = "<Press a key>";
}

void	settings_button(int buttonID)
{
	(void)buttonID;
	for (int i = 0; game.resources.buttons[i].content; i++)
		game.resources.buttons[i].active = false;
	for (int i = 3; i < 9; i++) {
		game.resources.buttons[i].active = i != 3;
		game.resources.buttons[i].displayed = true;
	}
}

void	quit_button(int buttonID)
{
	(void)buttonID;
	sfRenderWindow_close(game.resources.window);
}
