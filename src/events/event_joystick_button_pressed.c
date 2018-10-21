#include <structs.h>
#include <callbacks.h>
#include <save.h>
#include <utils.h>
#include <menus.h>

void	manageJoystickButtonPressed(sfEvent *event)
{
	int	offset = game.languagesConf.y + game.languagesConf.x;

	if (
		(game.state.menu == IN_GAME_MENU || game.state.menu == BATTLE_MENU) &&
		game.settings.keys[KEY_PAUSE] == event->joystickButton.button + 205
	) {
		backOnTitleScreen(-1);
		saveGame(true);
		return;
	}
	if (
		game.state.menuSelected - offset >= 0 &&
		game.state.menuSelected - offset < 4 &&
		game.state.menu == CONTROLS_MENU
	)
		for (int i = 0; i < 4; i++)
			if (game.settings.keys[i] >= 201 && game.settings.keys[i] <= 204) {
				game.settings.keys[i] = 255;
				game.resources.buttons[i + offset].content = getKeyString(255);
			}
	if (game.state.menuSelected - offset >= 0 && game.state.menu == CONTROLS_MENU) {
		game.settings.keys[game.state.menuSelected - offset] = event->joystickButton.button + 205;
		game.resources.buttons[game.state.menuSelected].content = getKeyString(event->joystickButton.button + 205);
		game.state.menuSelected = -1;
	}
}