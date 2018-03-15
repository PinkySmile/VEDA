#include <stdio.h>
#include "structs.h"
#include "functions.h"
#include "macros.h"

void	launchGame(game_t *game)
{
	printf("%s: Launching game\n", INFO);
	while (sfRenderWindow_isOpen(game->window)) {
		manageEvents(game);
		sfRenderWindow_clear(game->window, (sfColor){0, 0, 0, 255});
		mainMenu(game);
		sfRenderWindow_display(game->window);
	}
}
