#include "structs.h"
#include "functions.h"

void	manageEvents(game_t *game)
{
	sfEvent	event;

	while (sfRenderWindow_pollEvent(game->window, &event))
		if (event.type == sfEvtClosed) {
			sfRenderWindow_close(game->window);
			for (int i = 0; i < game->musics.length; i++)
				if (((sfMusic **)game->musics.content)[i] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
					sfMusic_stop(((sfMusic **)game->musics.content)[i]);
		} else if (event.type == sfEvtMouseButtonPressed)
			manage_mouse_click(game);
}
