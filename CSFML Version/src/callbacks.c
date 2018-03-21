#include "structs.h"
#include "functions.h"

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
}

void	play_button(game_t *game, int buttonID)
{
	(void)buttonID;
	game->menu = 1;
	for (int i = 0; game->buttons[i].content; i++) {
		game->buttons[i].active = false;
		game->buttons[i].displayed = false;
	}
}

void	options_button(game_t *game, int buttonID)
{

}

void	audio_button(game_t *game, int buttonID)
{

}

void	lang_button(game_t *game, int buttonID)
{

}

void	controls_button(game_t *game, int buttonID)
{

}

void	settings_button(game_t *game, int buttonID)
{
	(void)buttonID;
	for (int i = 0; game->buttons[i].content; i++)
		game->buttons[i].active = false;
	for (int i = 3; i < 10; i++) {
		game->buttons[i].active = true;
		game->buttons[i].displayed = true;
	}
	game->buttons[0].active = true;
	game->buttons[0].displayed = true;
}

void	quit_button(game_t *game, int buttonID)
{
	(void)buttonID;
	sfRenderWindow_close(game->window);
}
