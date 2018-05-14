#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include <malloc.h>

void	audio(game_t *game)
{
	char	*nbrs[2];

	for (int i = 0; i < 640; i += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x) {
		if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y) {
			image(game, ((Sprite *)game->sprites.content)[MENU_BACKGROUND].sprite, i, j, -1, -1);
			if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y == 0)
				break;
		}
	}
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){100, 100, 100, 255});
	rect(game, 0, 0, 512, 48);
	rect(game, 0, 48, 512, 48);
	rect(game, 0, 0, 512, 48);
	rect(game, 0, 48, 512, 48);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){255, 255, 255, 255});
	rect(game, 140, 14, 300, 20);
	rect(game, 140, 62, 300, 20);
	sfRectangleShape_setFillColor(game->rectangle, (sfColor){255, 0, 0, 255});
	rect(game, 130 + game->settings.sfxVolume * 3, 6, 20, 36);
	rect(game, 130 + game->settings.musicVolume * 3, 54, 20, 36);
	text("Sound effects", game, 5, 8);
	text("Musics", game, 5, 56);
	nbrs[0] = concatf("%i%%", game->settings.sfxVolume);
	nbrs[1] = concatf("%i%%", game->settings.musicVolume);
	if (nbrs[0])
		text(nbrs[0], game, 455, 8);
	if (nbrs[1])
		text(nbrs[1], game, 455, 56);
	free(nbrs[0]);
	free(nbrs[1]);
}

void	options(game_t *game)
{
	for (int i = 0; i < 640; i += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x) {
		if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y) {
			image(game, ((Sprite *)game->sprites.content)[MENU_BACKGROUND].sprite, i, j, -1, -1);
			if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y == 0)
				break;
		}
	}
	for (int i = 0; i <= 2; i++) {
		if (game->settings.windowMode == i) {
			game->buttons[i + 10].textColor = (sfColor){0, 120, 0, 255};
			game->buttons[i + 10].color = (sfColor){220, 220, 0, 255};
		} else {
			game->buttons[i + 10].textColor = (sfColor){0, 0, 0, 255};
			game->buttons[i + 10].color = (sfColor){205, 205, 205, 255};
		}
	}
	if (game->settings.dispFramerate)
		game->buttons[13].color = (sfColor){0, 255, 0, 255};
	else
		game->buttons[13].color = (sfColor){255, 0, 0, 255};
}

void	controls(game_t *game)
{
	for (int i = 0; i < 640; i += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x) {
		if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y) {
			image(game, ((Sprite *)game->sprites.content)[MENU_BACKGROUND].sprite, i, j, -1, -1);
			if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y == 0)
				break;
		}
	}
	if (getLanguage(game->languages, game->settings.lang_id) < 0 || game->languages[getLanguage(game->languages, game->settings.lang_id)].keys == NULL)
		return;
	for (int i = 0; game->languages[getLanguage(game->languages, game->settings.lang_id)].keys[i] && i < NB_OF_KEYS; i++) {
		sfRectangleShape_setFillColor(game->rectangle, (sfColor){100, 100, 100, 255});
		rect(game, i / 10 * 272, i % 10 * 48, 272, 48);
		sfText_setCharacterSize(game->text, 17);
		sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
		if (game->settings.keys[i] == (unsigned char)-1)
			sfText_setColor(game->text, (sfColor){0, 0, 0, 255});
		else
			for (int j = 0; j < NB_OF_KEYS; j++)
				if ((j != i && game->settings.keys[j] == game->settings.keys[i])) {
					sfText_setColor(game->text, (sfColor){255, 0, 0, 255});
					break;
				}
		text(game->languages[getLanguage(game->languages, game->settings.lang_id)].keys[i], game, 5 + i / 10 * 272, i % 10 * 48 + 15);
	}
}