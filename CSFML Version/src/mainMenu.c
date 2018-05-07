#include "structs.h"
#include "functions.h"

void	mainMenu(game_t *game)
{
	//static float var = 1;

	//var -= 0.0001 * var;
	//sfMusic_setPitch(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC], var);
	if (!sfRenderWindow_isOpen(game->window))
		return;
	if (((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) != sfPlaying)
		sfMusic_play(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]);
	for (int i = 0; i < 640; i += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x) {
		if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y) {
			image(game, ((Sprite *)game->sprites.content)[MENU_BACKGROUND].sprite, i, j, -1, -1);
			if (((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y == 0)
				break;
		}
	}
	if (game->debug && game->text) {
		sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
		text("Debug mode", game, 520, 17);
		sfText_setColor(game->text, (sfColor){0, 0, 0, 255});
	}
}
