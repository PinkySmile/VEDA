#include "structs.h"
#include "functions.h"

void	launchGame(game_t *game)
{
	while (sfRenderWindow_isOpen(game->window)) {
		manageEvents(game);
		sfRenderWindow_clear(game->window, (sfColor){0, 0, 0, 255});
		sfRenderWindow_display(game->window);
	}
}