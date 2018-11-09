#include <structs.h>
#include "menus.h"

void	manageMouseReleased()
{
	if (game.state.menu == OPTIONS_MENU || game.state.menu == AUDIO_MENU)
		game.state.menuSelected = -1;
}
