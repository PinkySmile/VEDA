#include <structs.h>

void	manageMouseReleased()
{
	if (game.state.menu == 3)
		game.state.menuSelected = -1;
}
