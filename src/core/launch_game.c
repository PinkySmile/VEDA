#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "discord_rp.h"
#include "display.h"
#include "concatf.h"
#include "graphic.h"
#include "save.h"
#include "structs.h"
#include "functions.h"
#include "macros.h"
#include "menus.h"
#include "configs.h"
#include "utils.h"

void	displayFramerate()
{
	char		frameRate[20];
	static	sfClock	*clock = NULL;

	if (!clock)
		clock = sfClock_create();
	memset(frameRate, 0, sizeof(frameRate));
	sprintf(frameRate, "%.3f FPS", 1 / sfTime_asSeconds(sfClock_getElapsedTime(clock)));
	sfText_setCharacterSize(game.resources.text, 10);
	sfText_setColor(game.resources.text, (sfColor){255, 255, 255, 255});
	text(frameRate, 2, 0, false);
	sfClock_restart(clock);
}

void	debug_displayPosition()
{
	static	int	color = 255;
	Character	*player = getPlayer();
	char		*tmp;

	sfText_setCharacterSize(game.resources.text, 10);
	tmp = concatf(
		"X: %f\nY: %f\ncamX: %i\ncamY: %i\n",
		player->movement.pos.x,
		player->movement.pos.y,
		game.state.cameraPos.x,
		game.state.cameraPos.y
	);
	sfText_setColor(game.resources.text, (sfColor) {abs(color), abs(color), abs(color), 255});
	text(tmp, 0, game.settings.dispFramerate ? 10 : 0, false);
	free(tmp);
	color--;
	if (color < -255)
		color *= -1;
}

void	displayDebugElements()
{
	sfText_setCharacterSize(game.resources.text, 10);
	text("Debug mode", 580, 0, false);
	sfText_setColor(game.resources.text, (sfColor){255, 255, 255, 255});
	switch (game.state.menu) {
	case IN_GAME_MENU:
		debug_displayPosition();
		break;
	case BATTLE_MENU:
		debug_displayPosition();
		break;
	}
}

void	launchGame()
{
	printf("%s: Launching game\n", INFO_BEG);
	updateDiscordPresence("Main menu", "In Main Menu", 0, false, "icon", "nem", "VEDA", "Main Menu");
	while (sfRenderWindow_isOpen(game.resources.window)) {
		sfRenderWindow_clear(game.resources.window, (sfColor){0, 0, 0, 255});
		game_functions[game.state.menu]();
		dispButtons();
		manageEvents();
		if (game.settings.dispFramerate)
			displayFramerate();
		if (game.debug)
			displayDebugElements();
		sfRenderWindow_display(game.resources.window);
	}
	saveSettings();
}
