#include "structs.h"
#include "functions.h"

void	displayLowerLayer(game_t *game)
{
	Object		*map = game->map;
	Array		sprites = game->sprites;
	sfVector2i	cam = game->cam;
	sfIntRect	rec = {0, 0, 16, 16};

	for (int i = 0; map && map[i].layer; i++) {
		if (map[i].layer == 1 && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			if (!((Sprite *)sprites.content)[OBJECTS].sprite) {
				sfRectangleShape_setFillColor(game->rectangle, (sfColor){((map[i].id * 10) >> 16) * 20 % 256, ((map[i].id * 10) >> 8) * 10 % 256, map[i].id * 10 % 256, 255});
				rect(game, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 32, 32);
			} else {
				rec.left = (map[i].id - 1) * 16 % 640;
				rec.top = (map[i].id - 1) * 16 / 640;
				sfSprite_setTextureRect(((Sprite *)sprites.content)[OBJECTS].sprite, rec);
				image(game, ((Sprite *)sprites.content)[OBJECTS].sprite,  map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
			}
		}
	}
}

void	displayCharacters(game_t *game)
{
	Player		player = game->player;
	sfIntRect	rec = {0, 0, 16, 32};
	Array		sprites = game->sprites;
	sfVector2i	cam = game->cam;

	rec.top = player.position / 2 + (player.state * 2) + (player.animation * 2);
	rec.left = player.state / 2 % 2;
	sfSprite_setTextureRect(((Sprite *)sprites.content)[MALE_CHARACTER + player.isFemale].sprite, rec);
	image(game, ((Sprite *)sprites.content)[MALE_CHARACTER + player.isFemale].sprite,  player.pos.x + cam.x, player.pos.y + cam.y, 16, 32);
}

void	displayUpperLayer(game_t *game)
{
	Object		*map = game->map;
	Array		sprites = game->sprites;
	sfVector2i	cam = game->cam;
	sfIntRect	rec = {0, 0, 32, 32};
	bool		newLayer = true;

	for (int layer = 2; newLayer; layer++) {
		newLayer = false;
		for (int i = 0; map && map[i].layer; i++) {
			if (map[i].layer == layer && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
				if (!((Sprite *)sprites.content)[OBJECTS].sprite) {
					sfRectangleShape_setFillColor(game->rectangle, (sfColor){((map[i].id * 10) >> 16) * 20 % 256, ((map[i].id * 10) >> 8) * 10 % 256, map[i].id * 10 % 256, 255});
					rect(game, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 32, 32);
				} else {
					rec.left = map[i].id * 32 % 1280;
					rec.top = map[i].id * 32 / 1280;
					sfSprite_setTextureRect(((Sprite *)sprites.content)[OBJECTS].sprite, rec);
					image(game, ((Sprite *)sprites.content)[OBJECTS].sprite,  map[i].pos.x + cam.x, map[i].pos.y + cam.y, 32, 32);
				}
			}
			newLayer = newLayer || map[i].layer > layer;
		}
	}
}

void	inGame(game_t *game)
{
	displayLowerLayer(game);
	displayCharacters(game);
	//displayUpperLayer(game);
}