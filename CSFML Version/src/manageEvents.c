#include "structs.h"

void	manageEvents(game_t *game)
{
	sfEvent	event;

	while (sfRenderWindow_pollEvent(game->window, &event))
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(game->window);
}