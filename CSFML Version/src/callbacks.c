#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include <stdlib.h>
#include <string.h>

void	back_on_title_screen(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	for (int i = 0; i < 3; i++) {
		game->buttons[i].active = true;
		game->buttons[i].displayed = true;
	}
	game->menu = 0;
}

void	play_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->menu = 1;
	free(game->map);
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->map = loadLevel("data/levels/test/level/floor0.lvl", &game->bg);
	if (((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) == sfPlaying)
		sfMusic_stop(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]);
}

void	changeKey(game_t *game, int buttonID)
{
	if (game->selected >= 0)
		game->buttons[game->selected].content = getKeyString(game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x]);
	game->selected = buttonID;
	if (game->settings.keys[game->selected - game->languagesConf.y - game->languagesConf.x] >= 105)
		free(game->buttons[game->selected].content);
	game->buttons[game->selected].content = "<Press a key>";
}

void	options_button(game_t *game, int buttonID)
{

}

void	audio_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->menu = 3;
	game->selected = 0;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
}

void	lang_button(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
	for (int i = 0; i < game->languagesConf.y; i++) {
		game->buttons[i + game->languagesConf.x].active = true;
		game->buttons[i + game->languagesConf.x].displayed = true;
	}
}

void	controls_button(game_t *game, int buttonID)
{
	game->selected = -1;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	for (int i = 0; i < NB_OF_KEYS; i++) {
		game->buttons[i + game->languagesConf.x + game->languagesConf.y].active = true;
		game->buttons[i + game->languagesConf.x + game->languagesConf.y].displayed = true;
		game->buttons[i + game->languagesConf.x + game->languagesConf.y].content = getKeyString(game->settings.keys[i]);
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
	game->menu = 2;
}

void	settings_button(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++)
		game->buttons[i].active = false;
	for (int i = 3; i < 9; i++) {
		game->buttons[i].active = i != 3;
		game->buttons[i].displayed = true;
	}
}

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
		for (int j = 0; j < NB_OF_KEYS; j++)
			if ((j != i && game->settings.keys[j] == game->settings.keys[i]) || game->settings.keys[j] == -1) {
				sfText_setColor(game->text, (sfColor){255, 0, 0, 255});
				break;
			}
		text(game->languages[getLanguage(game->languages, game->settings.lang_id)].keys[i], game, 5 + i / 10 * 272, i % 10 * 48 + 15);
	}
}

void	changeLanguage(game_t *game, int buttonID)
{
	strcpy(game->settings.lang_id, game->languages[buttonID - game->languagesConf.x].id);
	for (int i = 0; game->buttons[i].content; i++) {
		printf("%s: Destroying button %i\n", INFO, i);
		sfRectangleShape_destroy(game->buttons[i].rect);
	}
	free(game->buttons);
	game->buttons = loadButtons(game);
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
	game->buttons[9].active = true;
	game->buttons[9].displayed = true;
	for (int i = 0; i < game->languagesConf.y; i++) {
		game->buttons[i + game->languagesConf.x].active = true;
		game->buttons[i + game->languagesConf.x].displayed = true;
	}
}

void	quit_button(game_t *game, int buttonID)
{
	(void)buttonID;
	sfRenderWindow_close(game->window);
}
