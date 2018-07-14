#include "structs.h"
#include "discord_rp.h"
#include "functions.h"

void	mainMenu(game_t *game)
{
	//static float var = 1;

	//var -= 0.0001 * var;
	//sfMusic_setPitch(((sfMusic **)game->musics.content)[MAIN_MENU_MUSIC], var);
	updateDiscordPresence("Main menu", "In Main Menu", 0, false, "icon", "nem", "VEDA", "Main Menu");
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
}
