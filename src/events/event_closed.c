#include <SFML/Graphics.h>
#include "structs.h"
#include "save.h"
#include "menus.h"

void	manageEventClosed()
{
	sfRenderWindow_close(game.resources.window);
	if (game.state.menu == IN_GAME_MENU || game.state.menu == BATTLE_MENU)
		saveGame(true);
	for (int i = 0; i < game.resources.musics.length; i++)
		if (getMusic(i) && sfMusic_getStatus(getMusic(i)) == sfPlaying)
			sfMusic_stop(getMusic(i));
}