#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdbool.h>
#include "menus.h"
#include "structs.h"

bool	buttonIsClicked(Button button, sfVector2f click_pos)
{
	sfVector2f	size = {
		button.size.x * game.settings.baseScale.x,
		button.size.y * game.settings.baseScale.y
	};
	sfVector2f	pos = {
		button.pos.x * game.settings.baseScale.x,
		button.pos.y * game.settings.baseScale.y
	};
	bool		is_in_y = click_pos.x < pos.x + size.x &&
			click_pos.x > pos.x;
	bool		is_in_x = click_pos.y < pos.y + size.y &&
			click_pos.y > pos.y;

	return (is_in_y && is_in_x && button.active);
}

void	whichButton(sfVector2f pos)
{
	for (int i = 0; game.resources.buttons[i].content; i++)
		if (buttonIsClicked(game.resources.buttons[i], pos)) {
			printf("%s: Clicked on button %i (%s)\n", INFO_BEG, i, game.resources.buttons[i].content);
			game.resources.buttons[i].callback(i);
			break;
		}
}

void	manageMouseClick(sfMouseButtonEvent event)
{
	sfVector2f	pos = {event.x, event.y};

	if (game.state.menu == AUDIO_MENU) {
		if (
			pos.x >= 140 * game.settings.baseScale.x &&
			pos.x <= 440 * game.settings.baseScale.x &&
			pos.y >= 4 * game.settings.baseScale.y &&
			pos.y <= 44 * game.settings.baseScale.y
		) {
			game.state.menuSelected = 1;
			if (pos.x <= 140)
				game.settings.sfxVolume = 0;
			else if (pos.x >= 440)
				game.settings.sfxVolume = 100;
			else
				game.settings.sfxVolume = (pos.x - 140) / 3;
			printf("%s: Clicked on sfx volume control\n", INFO_BEG);

		} else if (
			pos.x >= 140 * game.settings.baseScale.x &&
			pos.x <= 440 * game.settings.baseScale.x &&
			pos.y >= 52 * game.settings.baseScale.y &&
			pos.y <= 92 * game.settings.baseScale.y
		) {
			game.state.menuSelected = 2;
			if (pos.x <= 140)
				game.settings.musicVolume = 0;
			else if (pos.x >= 440)
				game.settings.musicVolume = 100;
			else
				game.settings.musicVolume = (pos.x - 140) / 3;
			printf("%s: Clicked on music volume control\n", INFO_BEG);
		}
	}
	if (event.button == sfMouseLeft)
		whichButton(pos);
}
