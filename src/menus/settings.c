#include <malloc.h>
#include "utils.h"
#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "graphic.h"

void	audio()
{
	char	*nbrs[2];

	for (int i = 0; i < 640; i += getSprite(MENU_BACKGROUND)->size.x) {
		if (((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += getSprite(MENU_BACKGROUND)->size.y) {
			image(getSprite(MENU_BACKGROUND)->sprite, i, j, -1, -1);
			if (getSprite(MENU_BACKGROUND)->size.y == 0)
				break;
		}
	}

	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){100, 100, 100, 255});
	rect(0, 0, 512, 96);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){255, 255, 255, 255});
	rect(140, 14, 300, 20);
	rect(140, 62, 300, 20);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){255, 0, 0, 255});
	rect(130 + game.settings.sfxVolume * 3, 6, 20, 36);
	rect(130 + game.settings.musicVolume * 3, 54, 20, 36);
	sfText_setCharacterSize(game.resources.text, 20);
	text("Sound effects", 5, 8, false);
	text("Musics", 5, 56, false);
	nbrs[0] = concatf("%i%%", game.settings.sfxVolume);
	nbrs[1] = concatf("%i%%", game.settings.musicVolume);
	if (nbrs[0])
		text(nbrs[0], 455, 8, false);
	if (nbrs[1])
		text(nbrs[1], 455, 56, false);
	free(nbrs[0]);
	free(nbrs[1]);
}

void	options()
{
	char		*buffer;
	sfVector2u	newSize = game.newSize;

	for (int i = 0; i < 640; i += getSprite(MENU_BACKGROUND)->size.x) {
		if (((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += getSprite(MENU_BACKGROUND)->size.y) {
			image(getSprite(MENU_BACKGROUND)->sprite, i, j, -1, -1);
			if (getSprite(MENU_BACKGROUND)->size.y == 0)
				break;
		}
	}
	for (enum windowMode i = WINDOWED; i < NUMBER_OF_WINDOW_MODES; i++) {
		if (game.newMode == i) {
			game.resources.buttons[i + 10].textColor = (sfColor){0, 120, 0, 255};
			game.resources.buttons[i + 10].color = (sfColor){220, 220, 0, 255};
		} else {
			game.resources.buttons[i + 10].textColor = (sfColor){0, 0, 0, 255};
			game.resources.buttons[i + 10].color = (sfColor){205, 205, 205, 255};
		}
	}
	if (game.settings.dispFramerate)
		game.resources.buttons[13].color = (sfColor){0, 255, 0, 255};
	else
		game.resources.buttons[13].color = (sfColor){255, 0, 0, 255};
	if (
		game.settings.windowMode == game.newMode && (
			(game.settings.windowSize.x == newSize.x && game.settings.windowSize.y == newSize.y) ||
			game.newMode == FULLSCREEN
		)
	) {
		game.resources.buttons[15].color = (sfColor){0, 0, 0, 255};
		game.resources.buttons[15].textColor = (sfColor){155, 155, 155, 255};
		game.resources.buttons[15].shadeStep = -4;
	} else {
		game.resources.buttons[15].color = (sfColor){205, 205, 205, 255};
		game.resources.buttons[15].textColor = (sfColor){0, 0, 0, 255};
		game.resources.buttons[15].shadeStep = 15;
	}

	sfText_setColor(game.resources.text, (sfColor){255, 255, 255, 255});
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){100, 100, 100, 255});
	rect(232, 100, 512, 96);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){255, 255, 255, 255});
	rect(272, 109, 300, 20);
	rect(272, 147, 300, 20);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){255, 0, 0, 255});
	rect(262 + (game.newSize.x - 256) * 300 / (game.state.currentDesktopMode.width - 256), 101, 20, 36);
	rect(262 + (game.newSize.y - 144) * 300 / (game.state.currentDesktopMode.height - 144), 139, 20, 36);
	sfText_setCharacterSize(game.resources.text, 20);
	text("X:", 240, 104, false);
	text("Y:", 240, 142, false);
	buffer = concatf("%ux%u", game.newSize.x, game.newSize.y);
	if (buffer)
		text(buffer, 252, 172, false);
}

void	controls()
{
	for (int i = 0; i < 640; i += getSprite(MENU_BACKGROUND)->size.x) {
		if (getSprite(MENU_BACKGROUND)->size.x == 0)
			break;
		for (int j = 0; j < 640; j += getSprite(MENU_BACKGROUND)->size.y) {
			image(getSprite(MENU_BACKGROUND)->sprite, i, j, -1, -1);
			if (getSprite(MENU_BACKGROUND)->size.y == 0)
				break;
		}
	}
	if (!getLanguage(findLanguage(game.settings.lang_id)) || !getLanguage(findLanguage(game.settings.lang_id))->keys)
		return;
	for (int i = 0; game.resources.languages[findLanguage(game.settings.lang_id)].keys[i] && i < NB_OF_KEYS; i++) {
		sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){100, 100, 100, 255});
		rect(i / 10 * 272, i % 10 * 48, 272, 48);
		sfText_setCharacterSize(game.resources.text, 17);
		sfText_setColor(game.resources.text, (sfColor){255, 255, 255, 255});
		if (game.settings.keys[i] == (unsigned char)-1)
			sfText_setColor(game.resources.text, (sfColor){0, 0, 0, 255});
		else
			for (int j = 0; j < NB_OF_KEYS; j++)
				if ((j != i && game.settings.keys[j] == game.settings.keys[i])) {
					sfText_setColor(game.resources.text, (sfColor){255, 0, 0, 255});
					break;
				}
		text(getLanguage(findLanguage(game.settings.lang_id))->keys[i], 5 + i / 10 * 272, i % 10 * 48 + 15, false);
	}
}
