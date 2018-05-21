#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "concatf.h"
#include "structs.h"
#include "functions.h"
#include "macros.h"
#include "game_functions.h"

void	launchGame(game_t *game)
{
	static int	loopCount = 0;
	static int	oldTime = 0;
	static char	*frameRate = NULL;

	printf("%s: Launching game\n", INFO);
	while (sfRenderWindow_isOpen(game->window)) {
		sfRenderWindow_clear(game->window, (sfColor){0, 0, 0, 255});
		game_functions[game->menu](game);
		disp_buttons(game);
		manageEvents(game);
		loopCount++;
		if (oldTime != time(NULL)) {
			free(frameRate);
			frameRate = concatf("%f FPS", (float)loopCount / (time(NULL) - oldTime));
			loopCount = 0;
			oldTime = time(NULL);
		}
		if (game->settings.dispFramerate) {
			sfText_setCharacterSize(game->text, 10);
			sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
			text(frameRate, game, 2, 0);
		}
		if (game->debug) {
			sfText_setCharacterSize(game->text, 10);
			sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
			text("Debug mode", game, 580, 0);
			sfText_setColor(game->text, (sfColor){0, 0, 0, 255});
		}
		sfRenderWindow_display(game->window);
	}
	free(frameRate);
}
