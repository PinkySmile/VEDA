#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "discord_rp.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	back_on_title_screen(int buttonID)
{
	(void)buttonID;
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	for (int i = 0; i < 3; i++) {
		game.ressources.buttons[i].active = true;
		game.ressources.buttons[i].displayed = true;
	}
	for (int i = 0; i < game.ressources.musics.length; i++)
		if (((sfMusic **)game.ressources.musics.content)[i] && sfMusic_getStatus(((sfMusic **)game.ressources.musics.content)[i]) == sfPlaying)
			sfMusic_stop(((sfMusic **)game.ressources.musics.content)[i]);
	if (game.state.battle_infos.music && sfMusic_getStatus(game.state.battle_infos.music) == sfPlaying)
		sfMusic_stop(game.state.battle_infos.music);
	updateDiscordPresence("Main Menu", "In Main Menu", 0, false, "icon", 0, "VEDA", 0);
	game.state.menu = 0;
}

void	play_button(int buttonID)
{
	char	*buffer;

	(void)buttonID;
	free(game.state.loadedMap.objects);
	game.state.loadedMap.objects = NULL;
	loadGame();
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	if (!game.state.loadedMap.objects || !game.state.characters.content) {
		loadLevel("data/levels/test");
		game.state.loadedMap.path = strdup("data/levels/test");
	}
	if (strcmp(getPlayer(game.state.characters.content, game.state.characters.length)->name, "") == 0) {
		updateDiscordPresence("Main Menu", "Choosing name", 0, false, "icon", 0, "VEDA", 0);
		game.state.menu = 6;
		game.input.bufPos = 0;
		game.input.bufSize = 32;
		game.ressources.buttons[9].active = true;
		game.ressources.buttons[9].displayed = true;
		game.ressources.buttons[14].active = true;
		game.ressources.buttons[14].displayed = true;
		memset(game.input.buffer, 0, sizeof(*game.input.buffer) * 17);
	} else {
		buffer = concatf("Playing as \"%s\"", getPlayer(game.state.characters.content, game.state.characters.length)->name);
		updateDiscordPresence("In Game", buffer, 0, false, "icon", 0, "VEDA", 0);
		free(buffer);
		game.state.menu = 1;
	}
	if (((sfMusic **)game.ressources.musics.content)[MAIN_MENU_MUSIC] && sfMusic_getStatus(((sfMusic **)game.ressources.musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
		sfMusic_stop(((sfMusic **)game.ressources.musics.content)[MAIN_MENU_MUSIC]);
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
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	buffer = concatf("Playing as \"%s\"", player->name);
	updateDiscordPresence("In Game", buffer, 0, false, "icon", 0, "VEDA", 0);
	free(buffer);
}

void	fullScreen(int buttonID)
{
	(void)buttonID;
	changeScreenMode(FULLSCREEN);
}

void	borderless(int buttonID)
{
	(void)buttonID;
	changeScreenMode(BORDERLESS_WINDOW);
}

void	windowed(int buttonID)
{
	(void)buttonID;
	changeScreenMode(WINDOWED);
}

void	changeKey(int buttonID)
{
	if (game.state.menuSelected >= 0)
		game.ressources.buttons[game.state.menuSelected].content = getKeyString(game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x]);
	game.state.menuSelected = buttonID;
	if (game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x] > 204 && game.settings.keys[game.state.menuSelected - game.languagesConf.y - game.languagesConf.x] != (unsigned char)-1)
		free(game.ressources.buttons[game.state.menuSelected].content);
	game.ressources.buttons[game.state.menuSelected].content = "<Press a key>";
}

void	changeScreenMode(int new)
{
	char		*title = concat("VEDA version ", getVersion(), false, true);
	sfVideoMode	mode = {game.settings.windowSize.x, game.settings.windowSize.y, 32};
	sfWindowStyle	style;
	const sfUint8	*icon = NULL;

	game.state.menuSelected = 0;
	if (game.ressources.icon.image)
		icon = sfImage_getPixelsPtr(game.ressources.icon.image);
	else
		printf("%s: Couldn't load icon image\n", ERROR_BEG);
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL_BEG);
		dispMsg("Window error", "Couldn't create window title", 0);
		exit(EXIT_FAILURE);
	}
	if (game.settings.windowMode == new)
		return;
	game.settings.windowMode = new;
	if (game.settings.windowMode == FULLSCREEN) {
		style = sfFullscreen;
		mode = sfVideoMode_getDesktopMode();
	} else if (game.settings.windowMode == BORDERLESS_WINDOW) {
		style = sfNone;
		mode = sfVideoMode_getDesktopMode();
	} else
		style = sfTitlebar | sfClose;
	game.settings.baseScale.x = (float)mode.width / 640.0;
	game.settings.baseScale.y = (float)mode.height / 480.0;
	sfRenderWindow_close(game.ressources.window);
	sfRenderWindow_destroy(game.ressources.window);
	game.ressources.window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game.ressources.window) {
		printf("%s: Couldn't create window\n", FATAL_BEG);
		dispMsg("Window error", "Couldn't create window object", 0);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game.ressources.window, 32, 32, icon);
	sfRenderWindow_setFramerateLimit(game.ressources.window, 60);
}

void	options_button(int buttonID)
{
	(void)buttonID;
	game.state.menu = 4;
	game.state.menuSelected = 0;
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	for (int i = 9; i <= 13; i++) {
		game.ressources.buttons[i].active = true;
		game.ressources.buttons[i].displayed = true;
	}
}

void	FPS_button(int buttonID)
{
	(void)buttonID;
	game.settings.dispFramerate = !game.settings.dispFramerate;
}

void	audio_button(int buttonID)
{
	(void)buttonID;
	game.state.menu = 3;
	game.state.menuSelected = 0;
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	game.ressources.buttons[9].active = true;
	game.ressources.buttons[9].displayed = true;
}

void	lang_button(int buttonID)
{
	(void)buttonID;
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	game.ressources.buttons[9].active = true;
	game.ressources.buttons[9].displayed = true;
	for (int i = 0; i < game.languagesConf.y; i++) {
		game.ressources.buttons[i + game.languagesConf.x].active = true;
		game.ressources.buttons[i + game.languagesConf.x].displayed = true;
	}
}

void	controls_button(int buttonID)
{
	(void)buttonID;
	game.state.menuSelected = -1;
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	for (int i = 0; i < NB_OF_KEYS; i++) {
		game.ressources.buttons[i + game.languagesConf.x + game.languagesConf.y].active = true;
		game.ressources.buttons[i + game.languagesConf.x + game.languagesConf.y].displayed = true;
		game.ressources.buttons[i + game.languagesConf.x + game.languagesConf.y].content = getKeyString(game.settings.keys[i]);
	}
	game.ressources.buttons[9].active = true;
	game.ressources.buttons[9].displayed = true;
	game.state.menu = 2;
}

void	settings_button(int buttonID)
{
	(void)buttonID;
	for (int i = 0; game.ressources.buttons[i].content; i++)
		game.ressources.buttons[i].active = false;
	for (int i = 3; i < 9; i++) {
		game.ressources.buttons[i].active = i != 3;
		game.ressources.buttons[i].displayed = true;
	}
}

void	changeLanguage(int buttonID)
{
	strcpy(game.settings.lang_id, game.ressources.languages[buttonID - game.languagesConf.x].id);
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		printf("%s: Destroying button %i\n", INFO_BEG, i);
		sfRectangleShape_destroy(game.ressources.buttons[i].rect);
	}
	free(game.ressources.buttons);
	sfRenderWindow_setFramerateLimit(game.ressources.window, -1);
	game.ressources.buttons = loadButtons();
	sfRenderWindow_setFramerateLimit(game.ressources.window, 60);
	for (int i = 0; game.ressources.buttons[i].content; i++) {
		game.ressources.buttons[i].active = false;
		game.ressources.buttons[i].displayed = false;
	}
	game.ressources.buttons[9].active = true;
	game.ressources.buttons[9].displayed = true;
	for (int i = 0; i < game.languagesConf.y; i++) {
		game.ressources.buttons[i + game.languagesConf.x].active = true;
		game.ressources.buttons[i + game.languagesConf.x].displayed = true;
	}
}

void	quit_button(int buttonID)
{
	(void)buttonID;
	sfRenderWindow_close(game.ressources.window);
}
