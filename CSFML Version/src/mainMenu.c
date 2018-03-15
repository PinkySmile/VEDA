#include "structs.h"
#include "functions.h"

void	mainMenu(game_t *game)
{
	if (((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC] && sfMusic_getStatus(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]) != sfPlaying)
		sfMusic_play(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC]);
	for (int i = 0; i < 640; i += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.x)
		for (int j = 0; j < 640; j += ((Sprite *)game->sprites.content)[MENU_BACKGROUND].size.y)
			drawSprite(game->window, ((Sprite *)game->sprites.content)[MENU_BACKGROUND].sprite, i, j);
}