#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "discord_rp.h"
#include "display.h"
#include "concatf.h"
#include "graphic.h"
#include "save.h"
#include "structs.h"
#include "functions.h"
#include "macros.h"
#include "configs.h"

void	launchGame()
{
	static int	loopCount = 0;
	static int	oldTime = 0;
	static char	*frameRate = NULL;

	printf("%s: Launching game\n", INFO_BEG);
	updateDiscordPresence("Main menu", "In Main Menu", 0, false, "icon", "nem", "VEDA", "Main Menu");
	while (sfRenderWindow_isOpen(game.ressources.window)) {
		sfRenderWindow_clear(game.ressources.window, (sfColor){0, 0, 0, 255});
		game_functions[game.state.menu]();
		dispButtons();
		manageEvents();
		loopCount++;
		if (oldTime != time(NULL)) {
			free(frameRate);
			frameRate = concatf("%f FPS", (float)loopCount / (time(NULL) - oldTime));
			loopCount = 0;
			oldTime = time(NULL);
		}
		if (game.settings.dispFramerate) {
			sfText_setCharacterSize(game.ressources.text, 10);
			sfText_setColor(game.ressources.text, (sfColor){255, 255, 255, 255});
			text(frameRate, 2, 0, false);
		}
		if (game.debug) {
			sfText_setCharacterSize(game.ressources.text, 10);
			sfText_setColor(game.ressources.text, (sfColor){255, 255, 255, 255});
			text("Debug mode", 580, 0, false);
			sfText_setColor(game.ressources.text, (sfColor){0, 0, 0, 255});
		}
		sfRenderWindow_display(game.ressources.window);
	}
	free(frameRate);
	saveSettings();
}
