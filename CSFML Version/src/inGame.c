#include "structs.h"
#include "functions.h"
#include <string.h>

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

	rec.top = (player.position / 2 + (player.state * 2) + (player.animation * 2)) * 32;
	rec.left = (player.position % 2) * 32;
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
	game->player.canMove = true;
	displayLowerLayer(game);
	displayCharacters(game);
	displayUpperLayer(game);
	if (game->player.state == MOVING && sfTime_asSeconds(sfClock_getElapsedTime(game->player.animationClock)) >= 0.3) {
		game->player.animation = !game->player.animation;
		sfClock_restart(game->player.animationClock);
	} else if (game->player.state == MOVING && sfTime_asSeconds(sfClock_getElapsedTime(game->player.stateClock)) >= 0.3) {
		game->player.state = STATIC;
		game->player.animation = 0;
	}
	if (game->player.canMove) {
		// for (int i = 0; map && map[i].layer; i++) {
			// if (game->player.pos.x > map[i].pos.x - 16 && game->player.pos.x <= map[i].pos.x + 16 && game->player.pos.y + 16 > map[i].pos.y && game->player.pos.y + 16 <= map[i].pos.y + 16)
				// game->player.blocked.left = false;
		// }
		if (!game->player.blocked.left && sfKeyboard_isKeyPressed(sfKeyLeft)) {
			game->player.pos.x -= 1;
			game->player.position = LEFT;
			game->player.state = MOVING;
			sfClock_restart(game->player.stateClock);
		} else if (!game->player.blocked.right && sfKeyboard_isKeyPressed(sfKeyRight)) {
			game->player.pos.x += 1;
			game->player.position = RIGHT;
			game->player.state = MOVING;
			sfClock_restart(game->player.stateClock);
		} else if (!game->player.blocked.up && sfKeyboard_isKeyPressed(sfKeyUp)) {
			game->player.pos.y -= 1;
			game->player.position = UP;
			game->player.state = MOVING;
			sfClock_restart(game->player.stateClock);
		} else if (!game->player.blocked.down && sfKeyboard_isKeyPressed(sfKeyDown)) {
			game->player.pos.y += 1;
			game->player.position = DOWN;
			game->player.state = MOVING;
			sfClock_restart(game->player.stateClock);
		}
	}
}
