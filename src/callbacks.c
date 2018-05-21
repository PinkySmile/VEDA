#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	back_on_title_screen(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	for (int i = 0; i < 3; i++) {
		game->buttons[i].active = true;
		game->buttons[i].displayed = true;
	}
	game->menu = 0;
}

void	play_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->menu = 1;
	free(game->map);
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	loadGame(game);
	if (!game->map)
		game->map = loadLevel("data/levels/test/level/floor0.lvl", &game->bg);
	if (((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
		sfMusic_stop(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]);
}

void	fullScreen(game_t *game, int buttonID)
{
	(void)buttonID;
	changeScreenMode(game, FULLSCREEN);
}

void	borderless(game_t *game, int buttonID)
{
	(void)buttonID;
	changeScreenMode(game, BORDERLESS_WINDOW);
}

void	windowed(game_t *game, int buttonID)
{
	(void)buttonID;
	changeScreenMode(game, WINDOWED);
}

void	changeKey(game_t *game, int buttonID)
{
	if (game->selected >= 0)
		game->buttons[game->selected].content = getKeyString(game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x]);
	game->selected = buttonID;
	if (game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x] > 204 && game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x] != (unsigned char)-1)
		free(game->buttons[game->selected].content);
	game->buttons[game->selected].content = "<Press a key>";
}

void	changeScreenMode(game_t *game, int new)
{
	char		*title = concat("VEDA version ", getVersion(), false, true);
	sfVideoMode	mode = {640, 480, 32};
	sfWindowStyle	style;
	const sfUint8	*icon = NULL;

	game->selected = 0;
	if (game->icon.image)
		icon = sfImage_getPixelsPtr(game->icon.image);
	else
		printf("[ERROR] : Couldn't load icon image\n");
	if (!title) {
		printf("%s: Couldn't create window title\n", FATAL);
		dispMsg("Window error", "Couldn't create window title", 0);
		exit(EXIT_FAILURE);
	}
	if (game->settings.windowMode == new)
		return;
	game->settings.windowMode = new;
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
	sfRenderWindow_close(game->window);
	sfRenderWindow_destroy(game->window);
	game->window = sfRenderWindow_create(mode, title, style, NULL);
	if (!game->window) {
		printf("%s: Couldn't create window\n", FATAL);
		dispMsg("Window error", "Couldn't create window object", 0);
		exit(EXIT_FAILURE);
	}
	if (icon)
		sfRenderWindow_setIcon(game->window, 32, 32, icon);
	sfRenderWindow_setFramerateLimit(game->window, 60);
}

void	options_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->menu = 4;
	game->selected = 0;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	for (int i = 9; i <= 13; i++) {
		game->buttons[i].active = true;
		game->buttons[i].displayed = true;
	}
}

void	FPS_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->settings.dispFramerate = !game->settings.dispFramerate;
}

void	audio_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->menu = 3;
	game->selected = 0;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
}

void	lang_button(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
	for (int i = 0; i < game->languagesConf.y; i++) {
		game->buttons[i + game->languagesConf.x].active = true;
		game->buttons[i + game->languagesConf.x].displayed = true;
	}
}

void	controls_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->selected = -1;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	for (int i = 0; i < NB_OF_KEYS; i++) {
		game->buttons[i + game->languagesConf.x + game->languagesConf.y].active = true;
		game->buttons[i + game->languagesConf.x + game->languagesConf.y].displayed = true;
		game->buttons[i + game->languagesConf.x + game->languagesConf.y].content = getKeyString(game->settings.keys[i]);
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
	game->menu = 2;
}

void	settings_button(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++)
		game->buttons[i].active = false;
	for (int i = 3; i < 9; i++) {
		game->buttons[i].active = i != 3;
		game->buttons[i].displayed = true;
	}
}

void	changeLanguage(game_t *game, int buttonID)
{
	strcpy(game->settings.lang_id, game->languages[buttonID - game->languagesConf.x].id);
	for (int i = 0; game->buttons[i].content; i++) {
		printf("%s: Destroying button %i\n", INFO, i);
		sfRectangleShape_destroy(game->buttons[i].rect);
	}
	free(game->buttons);
	sfRenderWindow_setFramerateLimit(game->window, -1);
	game->buttons = loadButtons(game);
	sfRenderWindow_setFramerateLimit(game->window, 60);
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
	for (int i = 0; i < game->languagesConf.y; i++) {
		game->buttons[i + game->languagesConf.x].active = true;
		game->buttons[i + game->languagesConf.x].displayed = true;
	}
}

void	quit_button(game_t *game, int buttonID)
{
	(void)buttonID;
	sfRenderWindow_close(game->window);
}
