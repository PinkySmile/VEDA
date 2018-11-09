#include "structs.h"
#include "utils.h"

void	options_button(int buttonID)
{
	(void)buttonID;
	game.state.menu = 4;
	game.state.menuSelected = 0;
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	for (int i = 9; i <= 13; i++) {
		game.resources.buttons[i].active = true;
		game.resources.buttons[i].displayed = true;
	}
	game.resources.buttons[15].active = game.settings.windowMode == WINDOWED;
	game.resources.buttons[15].displayed = game.settings.windowMode == WINDOWED;
	game.newSize = game.settings.windowSize;
}

void	audio_button(int buttonID)
{
	(void)buttonID;
	game.state.menu = 3;
	game.state.menuSelected = 0;
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	game.resources.buttons[9].active = true;
	game.resources.buttons[9].displayed = true;
}

void	lang_button(int buttonID)
{
	(void)buttonID;
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	game.resources.buttons[9].active = true;
	game.resources.buttons[9].displayed = true;
	for (int i = 0; i < game.languagesConf.y; i++) {
		game.resources.buttons[i + game.languagesConf.x].active = true;
		game.resources.buttons[i + game.languagesConf.x].displayed = true;
	}
}

void	controls_button(int buttonID)
{
	(void)buttonID;
	game.state.menuSelected = -1;
	for (int i = 0; game.resources.buttons[i].content; i++) {
		game.resources.buttons[i].active = false;
		game.resources.buttons[i].displayed = false;
	}
	for (int i = 0; i < NB_OF_KEYS; i++) {
		game.resources.buttons[i + game.languagesConf.x + game.languagesConf.y].active = true;
		game.resources.buttons[i + game.languagesConf.x + game.languagesConf.y].displayed = true;
		game.resources.buttons[i + game.languagesConf.x + game.languagesConf.y].content = getKeyString(game.settings.keys[i]);
	}
	game.resources.buttons[9].active = true;
	game.resources.buttons[9].displayed = true;
	game.state.menu = 2;
}