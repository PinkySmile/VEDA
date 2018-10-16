#include "structs.h"
#include "discord_rp.h"
#include "functions.h"
#include "graphic.h"

void	mainMenu()
{
	//static float var = 1;

	//var -= 0.0001 * var;
	//sfMusic_setPitch(((sfMusic **)game.resources.musics.content)[MAIN_MENU_MUSIC], var);
	if (!sfRenderWindow_isOpen(game.resources.window))
		return;
	if (((sfMusic **)game.resources.musics.content)[MAIN_MENU_MUSIC] && sfMusic_getStatus(((sfMusic **)game.resources.musics.content)[MAIN_MENU_MUSIC]) != sfPlaying)
		sfMusic_play(((sfMusic **)game.resources.musics.content)[MAIN_MENU_MUSIC]);
	for (int i = 0; i < 640; i += ((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].size.x) {
		if (((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].size.x == 0)
			break;
		for (int j = 0; j < 640; j += ((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].size.y) {
			image(((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].sprite, i, j, -1, -1);
			if (((Sprite *)game.resources.sprites.content)[MENU_BACKGROUND].size.y == 0)
				break;
		}
	}
}
