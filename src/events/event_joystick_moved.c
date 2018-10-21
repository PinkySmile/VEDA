#include "utils.h"
#include "menus.h"
#include "structs.h"

void	manageJoystickMoved()
{
	int	offset = game.languagesConf.y + game.languagesConf.x;

	if (
		game.state.menuSelected - offset >= 0 &&
		game.state.menuSelected - offset < 4 &&
		game.state.menu == CONTROLS_MENU
	) {
		for (int i = 0; i < 4; i++) {
			game.settings.keys[i] = 201 + i;
			game.resources.buttons[i + game.languagesConf.y + game.languagesConf.x].content = getKeyString(201 + i);
		}
		game.resources.buttons[game.state.menuSelected].content = getKeyString(
			game.settings.keys[
				game.state.menuSelected - game.languagesConf.y - game.languagesConf.x
			]
		);
		game.state.menuSelected = -1;
	}
}