#include <string.h>
#include <SFML/Graphics.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include "loading.h"
#include "structs.h"

void	changeLanguage(int buttonID)
{
	strcpy(game.settings.lang_id, game.resources.languages[buttonID - game.languagesConf.x].id);
	for (int i = 0; game.resources.buttons[i].content; i++) {
		printf("%s: Destroying button %i\n", INFO_BEG, i);
		sfRectangleShape_destroy(game.resources.buttons[i].rect);
	}
	free(game.resources.buttons);
	sfRenderWindow_setFramerateLimit(game.resources.window, -1);
	game.resources.buttons = loadButtons();
	sfRenderWindow_setFramerateLimit(game.resources.window, 60);
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

void	FPS_button(int buttonID)
{
	(void)buttonID;
	game.settings.dispFramerate = !game.settings.dispFramerate;
}
