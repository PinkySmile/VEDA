#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
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
	sfVideoMode	max = sfVideoMode_getDesktopMode();

	if (game.state.menu == AUDIO_MENU) {
		if (
			pos.x >= 140 * game.settings.baseScale.x &&
			pos.x <= 440 * game.settings.baseScale.x &&
			pos.y >= 4 * game.settings.baseScale.y &&
			pos.y <= 44 * game.settings.baseScale.y
		) {
			game.state.menuSelected = 1;
			if (pos.x <= 140 * game.settings.baseScale.x)
				game.settings.sfxVolume = 0;
			else if (pos.x >= 440 * game.settings.baseScale.x)
				game.settings.sfxVolume = 100;
			else
				game.settings.sfxVolume = (pos.x / game.settings.baseScale.x - 140) / 3;
			if (getSoundEffect(DIRT1 + random() % 4))
				playSoundEffect(getSoundEffect(DIRT1 + random() % 4));
			printf("%s: Clicked on sfx volume control\n", INFO_BEG);

		} else if (
			pos.x >= 140 * game.settings.baseScale.x &&
			pos.x <= 440 * game.settings.baseScale.x &&
			pos.y >= 52 * game.settings.baseScale.y &&
			pos.y <= 92 * game.settings.baseScale.y
		) {
			game.state.menuSelected = 2;
			if (pos.x <= 140 * game.settings.baseScale.x)
				game.settings.musicVolume = 0;
			else if (pos.x >= 440 * game.settings.baseScale.x)
				game.settings.musicVolume = 100;
			else
				game.settings.musicVolume = (pos.x / game.settings.baseScale.x - 140) / 3;
			printf("%s: Clicked on music volume control\n", INFO_BEG);
		}
	} else if (game.state.menu == OPTIONS_MENU) {
		if (
			pos.x >= 272 * game.settings.baseScale.x &&
			pos.x <= 572 * game.settings.baseScale.x &&
			pos.y >= 101 * game.settings.baseScale.y &&
			pos.y <= 141 * game.settings.baseScale.y
		) {
			game.state.menuSelected = 1;
			if (pos.x <= 272 * game.settings.baseScale.x)
				game.newSize.x = 256;
			else if (pos.x >= 572 * game.settings.baseScale.x)
				game.newSize.x = max.width;
			else
				game.newSize.x = (pos.x / game.settings.baseScale.x - 272) * (max.width - 256) / 300 + 256;
			printf("%s: Clicked on sfx volume control\n", INFO_BEG);

		} else if (
			pos.x >= 272 * game.settings.baseScale.x &&
			pos.x <= 572 * game.settings.baseScale.x &&
			pos.y >= 139 * game.settings.baseScale.y &&
			pos.y <= 179 * game.settings.baseScale.y
		) {
			game.state.menuSelected = 2;
			if (pos.x <= 272 * game.settings.baseScale.x)
				game.newSize.y = 144;
			else if (pos.x >= 572 * game.settings.baseScale.x)
				game.newSize.y = max.height;
			else
				game.newSize.y = (pos.x / game.settings.baseScale.x - 272) * (max.height - 144) / 300 + 144;
			printf("%s: Clicked on music volume control\n", INFO_BEG);
		}
	}
	if (event.button == sfMouseLeft)
		whichButton(pos);
}
