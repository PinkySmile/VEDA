#include "structs.h"
#include "functions.h"
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

}

void	options_button(game_t *game, int buttonID)
{

}

void	audio_button(game_t *game, int buttonID)
{

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
		sfRectangleShape_setFillColor(game->rectangle, (sfColor){50, 50, 50, 255});
		rect(game, i / 10 * 272, i % 10 * 48, 272, 48);
		sfText_setCharacterSize(game->text, 17);
		sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
		text(game->languages[getLanguage(game->languages, game->settings.lang_id)].keys[i], game, 5 + i / 10 * 272, i % 10 * 48 + 15);
	}
}

void	changeLanguage(game_t *game, int buttonID)
{
	strcpy(game->settings.lang_id, game->languages[buttonID - game->languagesConf.x].id);
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
