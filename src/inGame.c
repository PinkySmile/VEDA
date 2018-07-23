#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void	displayLowerLayer(game_t *game)
{
	Object		*map = game->map;
	Array		sprites = game->sprites;
	sfVector2i	cam = game->cam;
	sfIntRect	rec = {0, 0, 16, 16};
	char		*buffer = NULL;

	for (int i = 0; map && map[i].layer; i++) {
		if (map[i].layer == 1 && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			if (!((Sprite *)sprites.content)[OBJECTS].sprite) {
				sfRectangleShape_setOutlineColor(game->rectangle, (sfColor){0, 0, 0, 0});
				sfRectangleShape_setFillColor(game->rectangle, (sfColor){((map[i].id * 10) >> 16) * 20 % 256, ((map[i].id * 10) >> 8) * 10 % 256, map[i].id * 10 % 256, 255});
				rect(game, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
			} else {
				rec.left = (map[i].id - 1) * 16 % 640;
				rec.top = (map[i].id - 1) * 16 / 640;
				sfSprite_setTextureRect(((Sprite *)sprites.content)[OBJECTS].sprite, rec);
				image(game, ((Sprite *)sprites.content)[OBJECTS].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
			}
			if (game->debug) {
				sfText_setCharacterSize(game->text, 15);
				sfText_setColor(game->text, (sfColor){0, 0, 0, 200});
				buffer = concatf("%i", map[i].id);
				text(buffer, game, map[i].pos.x + cam.x, map[i].pos.y + cam.y, false);
				free(buffer);
			}
		}
	}
}

void	displayCharacter(Character *character, game_t *game, int id, sfSprite *sprite)
{
	sfIntRect	rec = {0, 0, 16, 32};
	sfVector2i	cam = game->cam;

	if (character->movement.pos.x + cam.x < -16)
		return;
	if (character->movement.pos.y + cam.y < -32)
		return;
	if (character->movement.pos.x + cam.x > 640)
		return;
	if (character->movement.pos.y + cam.y > 480)
		return;
	rec.top = (character->movement.position / 2 + (character->movement.state * 2) + (character->movement.animation * 2)) * 32;
	rec.left = (character->movement.position % 2) * 32;
	if (sprite) {
		sfSprite_setTextureRect(sprite, rec);
		image(game, sprite, character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 16, 32);
	} else {
		sfRectangleShape_setOutlineColor(game->rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setFillColor(game->rectangle, (sfColor){id * 2 % 256, ((id * 10) >> 8) * 10 % 256, id * 2 % 256, 255});
		rect(game, character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 16, 32);
	}
}

void	displayCharacters(game_t *game)
{
	Character	buff;
	static int	var = 0;
	Array		sprites = game->sprites;

	for (int i = 0; i < game->characters.length; i++) {
		buff = ((Character *)game->characters.content)[i];
		if (MALE_CHARACTER + buff.texture >= 0 && MALE_CHARACTER + buff.texture < sprites.length && (!buff.invulnerabiltyTime || var % 5 <= 3))
			displayCharacter(&buff, game, i, ((Sprite *)sprites.content)[MALE_CHARACTER + buff.texture].sprite);
	}
	var = var >= 4 ? 0 : var + 1;
}

void	displayUpperLayer(game_t *game)
{
	Object		*map = game->map;
	Array		sprites = game->sprites;
	sfVector2i	cam = game->cam;
	sfIntRect	rec = {0, 0, 16, 16};
	bool		newLayer = true;
	char		*buffer = NULL;

	for (int nextLayer, layer = 2; newLayer; layer = nextLayer) {
		newLayer = false;
		nextLayer = 0;
		for (int i = 0; map && map[i].layer; i++) {
			if (map[i].layer == layer && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
				if (!((Sprite *)sprites.content)[OBJECTS].sprite) {
					sfRectangleShape_setOutlineColor(game->rectangle, (sfColor){0, 0, 0, 0});
					sfRectangleShape_setFillColor(game->rectangle, (sfColor){((map[i].id * 10) >> 16) * 20 % 256, ((map[i].id * 10) >> 8) * 10 % 256, map[i].id * 10 % 256, 255});
					rect(game, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
				} else {
					rec.left = (map[i].id - 1) * 16 % 640;
					rec.top = (map[i].id - 1) * 16 / 640;
					sfSprite_setTextureRect(((Sprite *)sprites.content)[OBJECTS].sprite, rec);
					image(game, ((Sprite *)sprites.content)[OBJECTS].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
				}
				if (game->debug) {
					sfText_setCharacterSize(game->text, 15);
					sfText_setColor(game->text, (sfColor){layer % 2 == 0 ? 255 : 0, layer % 3 == 0 ? 255 : 0, layer % 4 == 0 ? 255 : 0, 200});
					buffer = concatf("%i", map[i].id);
					text(buffer, game, map[i].pos.x + cam.x, map[i].pos.y + cam.y, false);
					free(buffer);
				}
			}
			nextLayer = map[i].layer > layer && (map[i].layer < nextLayer || nextLayer == 0) ? map[i].layer : nextLayer;
			newLayer = newLayer || map[i].layer > layer;
		}
	}
	for (int i = 0; game->debug && map && map[i].layer; i++) {
		if (map[i].solid && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			sfRectangleShape_setFillColor(game->rectangle, (sfColor){255, 0, 255, 125});
			rect(game, map[i].pos.x + cam.x + 1, map[i].pos.y + cam.y + 1, 14, 14);
		}
		if (((Sprite *)sprites.content)[MUSICS].sprite && map[i].action == CHANGE_MUSIC && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672)
			image(game, ((Sprite *)sprites.content)[MUSICS].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
		else if (((Sprite *)sprites.content)[CROSS].sprite && map[i].action == DEAL_DAMAGES && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			sfRectangleShape_setFillColor(game->rectangle, (sfColor){0, 0, 255, 155});
			rect(game, map[i].pos.x + cam.x + 3, map[i].pos.y + cam.y + 3, 10, 10);
		} else if (((Sprite *)sprites.content)[CUTSCENE].sprite && map[i].action == LAUNCH_CUTSCENE && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672)
			image(game, ((Sprite *)sprites.content)[CUTSCENE].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
	}
}

void	drawLifeBar(game_t *game)
{
	int		lifeBuffer = getPlayer(game->characters.content, game->characters.length)->stats.life;
	int		x = 0;
	int		y = 0;
	int		h = 0;
	int		b = 0;
	sfIntRect	rec = {0, 0, 16, 16};

	for (int i = 1 ; i <= getPlayer(game->characters.content, game->characters.length)->stats.lifeMax; i++) {
		if (lifeBuffer <= 10 && lifeBuffer > 0)
			rec.left = 48 + 160 * h + 16 * (10 - lifeBuffer);
		else if (lifeBuffer >= 10)
			rec.left = 48 + 160 * h;
		else
			rec.left = 528;
		if (((Sprite *)game->sprites.content)[LIFE_BAR].sprite) {
			sfSprite_setTextureRect(((Sprite *)game->sprites.content)[LIFE_BAR].sprite, rec);
			image(game, ((Sprite *)game->sprites.content)[LIFE_BAR].sprite, x, 465 - y, 16, 16);
			rec.left = 16 * h;
			sfSprite_setTextureRect(((Sprite *)game->sprites.content)[LIFE_BAR].sprite, rec);
			image(game, ((Sprite *)game->sprites.content)[LIFE_BAR].sprite, x, 465 - y, 16, 16);
		} else {
			sfRectangleShape_setFillColor(game->rectangle, (sfColor){h == 0 ? 255 : 0, h == 1 ? 255 : 0, h == 2 ? 255 : 0, 255});
			if (lifeBuffer <= 10 && lifeBuffer > 0)
				rect(game, x, 465 - y + 16 - 16 * lifeBuffer / 10, 16, 16 * lifeBuffer / 10);
			else if (lifeBuffer >= 10)
				rect(game, x, 465 - y, 16, 16);
		}
		if (b == 0)
			x = x + 15;
		if (b == 1) {
			h++;
			if (h == 3) {
				h = 0;
				x += 15;
			}
		}
		if (x >= 15 * 10) {
			x = 0;
			y += 15;
		}
		if (b == 0 && y >= 3 * 15) {
			h++;
			y = 0;
		}
		if (h == 3 && b == 0) {
			x = 0;
			b = 1;
			h = 0;
			y = y + 45;
		}
		if (y > 500)
			break;
		lifeBuffer = lifeBuffer - 10;
	}
}

void	drawEnergyBar(game_t *game)
{
	int		energyBuffer = getPlayer(game->characters.content, game->characters.length)->stats.energy;
	int		x = 0;
	int		y = 0;
	int		h = 0;
	int		b = 0;
	sfIntRect	rec = {0, 0, 16, 16};

	for (int i = 1 ; i <= getPlayer(game->characters.content, game->characters.length)->stats.maxEnergy ; i++) {
		if (energyBuffer <= 10 && energyBuffer > 0)
			rec.left = 48 + 160 * h + 16 * (10 - energyBuffer);
		else if (energyBuffer >= 10)
			rec.left = 48 + 160 * h;
		else
			rec.left = 528;
		if (((Sprite *)game->sprites.content)[ENERGY_BAR].sprite) {
			sfSprite_setTextureRect(((Sprite *)game->sprites.content)[ENERGY_BAR].sprite, rec);
			image(game, ((Sprite *)game->sprites.content)[ENERGY_BAR].sprite, 625 - x, 465 - y, 16, 16);
			rec.left = 16 * h;
			sfSprite_setTextureRect(((Sprite *)game->sprites.content)[ENERGY_BAR].sprite, rec);
			image(game, ((Sprite *)game->sprites.content)[ENERGY_BAR].sprite, 625 - x, 465 - y, 16, 16);
		} else {
			sfRectangleShape_setFillColor(game->rectangle, (sfColor){h == 0 ? 255 : 0, h == 1 ? 255 : 0, h == 2 ? 255 : 0, 255});
			if (energyBuffer <= 10 && energyBuffer > 0)
				rect(game, 625 - x, 465 - y + 16 - 16 * energyBuffer / 10, 16, 16 * energyBuffer / 10);
			else if (energyBuffer >= 10)
				rect(game, 625 - x, 465 - y, 16, 16);
		}
		if (b == 0)
			x = x + 15;
		if (b == 1) {
			h++;
			if (h == 3) {
				h = 0;
				x += 15;
			}
		}
		if (x >= 15 * 10) {
			x = 0;
			y += 15;
		}
		if (b == 0 && y >= 3 * 15) {
			h++;
			y = 0;
		}
		if (h == 3 && b == 0) {
			x = 0;
			b = 1;
			h = 0;
			y = y + 45;
		}
		if (y > 500)
			break;
		energyBuffer = energyBuffer - 10;
	}
}

void	displayHUD(game_t *game)
{
	drawEnergyBar(game);
	drawLifeBar(game);
}

void	dealDamages(Character *character, int damages, int damageType)
{
	float	buffer = character->stats.life;
	float	res = 0;

	if (damageType != TRUE_DAMAGE) {
		for (int i = 0; i < 5; i++)
			if (character->wornItems[i].name) {
				res += character->wornItems[i].resistances[damageType];
				if (character->wornItems[i].resistances[damageType] > 0) {
					character->wornItems[i].durability -= damages / 10;
					if (character->wornItems[i].durability <= 0)
						character->wornItems[i].name = NULL;
					for (int j = 0; character->wornItems[i].name != NULL && j < DAMAGES_TYPE_NB; j++)
						character->wornItems[i].resistances[j] = character->wornItems[i].baseResistances[j] * character->wornItems[i].durability / character->wornItems[i].baseDurability;
				}
			}
		character->stats.life -= damages * (20 / (sqrt(abs(res)) + 20));
	} else
		character->stats.life -= damages;
	if (character->stats.life > character->stats.lifeMax * 10)
		character->stats.life = character->stats.lifeMax * 10;
	if (character->stats.life < 0)
		character->stats.life = 0;
	if (character->stats.life - buffer != 0) {
		character->damageDisplay[damageType] -= buffer - character->stats.life;
		sfClock_restart(character->damageClock[damageType]);
	}
}

void	execAction(game_t *game, Object obj)
{
	Character	*player = getPlayer(game->characters.content, game->characters.length);

	if (obj.solid) {
		switch(player->movement.position) {
		case LEFT:
			player->movement.pos.x = obj.pos.x + 16;
			break;
		case RIGHT:
			player->movement.pos.x = obj.pos.x - 16;
			break;
		case UP:
			player->movement.pos.y = obj.pos.y + 1;
			break;
		case DOWN:
			player->movement.pos.y = obj.pos.y - 33;
			break;
		}
	}
	if (obj.footstepSound > game->stepSound)
		game->stepSound = obj.footstepSound + rand() % obj.footstepVariance;
	switch(obj.action) {
	case DEAL_DAMAGES:
		for (int i = 0; i < DAMAGES_TYPE_NB; i++) {
			if (obj.damages[i] && (player->invulnerabiltyTime <= 0 || obj.damages[i] < 0)) {
				dealDamages(player, obj.damages[i], i);
				player->invulnerabiltyTime = obj.invulnerabiltyTime > player->invulnerabiltyTime ? obj.invulnerabiltyTime : player->invulnerabiltyTime;
			}
		}
		break;
	case CHANGE_MUSIC:
		break;
	case LAUNCH_CUTSCENE:
		break;
	}
}

float	isPressed(int keyID, sfRenderWindow *window)
{
	if (!sfRenderWindow_hasFocus(window))
		return (0);
	sfJoystick_update();
	if (keyID <= 200)
		return (sfKeyboard_isKeyPressed(keyID));
	else if (keyID > 204)
		return (sfJoystick_isButtonPressed(0, keyID - 205));
	else if (keyID == 201)
		return (sfJoystick_getAxisPosition(0, sfJoystickY) > -3 ? 0 : -sfJoystick_getAxisPosition(0, sfJoystickY) / 100);
	else if (keyID == 202)
		return (sfJoystick_getAxisPosition(0, sfJoystickY) < 3 ? 0 : sfJoystick_getAxisPosition(0, sfJoystickY) / 100);
	else if (keyID == 203)
		return (sfJoystick_getAxisPosition(0, sfJoystickX) > -3 ? 0 : -sfJoystick_getAxisPosition(0, sfJoystickX) / 100);
	return (sfJoystick_getAxisPosition(0, sfJoystickX) < 3 ? 0 : sfJoystick_getAxisPosition(0, sfJoystickX) / 100);
}

Character	*getPlayer(Character *array, int len)
{
	for (int i = 0; i < len; i++)
		if (array[i].isPlayer)
			return (&array[i]);
	return (array);
}

void	movePlayer(game_t *game)
{
	Character	*player = getPlayer(game->characters.content, game->characters.length);
	Object		*map = game->map;
	bool		mooved = false;

	if (player->movement.pos.x + game->cam.x + 8 > 640) {
		game->cam.x -= 640;
	} else if (player->movement.pos.x + game->cam.x + 8 < 0) {
		game->cam.x += 640;
	} else if (player->movement.pos.y + game->cam.y + 16 > 480) {
		game->cam.y -= 480;
	} else if (player->movement.pos.y + game->cam.y + 16 < 0) {
		game->cam.y += 480;
	}
	if (player->movement.state == MOVING && sfTime_asSeconds(sfClock_getElapsedTime(player->movement.animationClock)) >= 0.1 / player->movement.speed) {
		player->movement.animation = !player->movement.animation;
		if (((sfMusic **)game->sfx.content)[game->stepSound])
			sfMusic_play(((sfMusic **)game->sfx.content)[game->stepSound]);
		sfClock_restart(player->movement.animationClock);
	} else if (player->movement.state == MOVING && sfTime_asSeconds(sfClock_getElapsedTime(player->movement.stateClock)) >= 0.3) {
		player->movement.state = STATIC;
		player->movement.animation = 0;
	}
	game->stepSound = IRON;
	if (player->movement.canMove) {
		memset(&player->movement.blocked, 0, sizeof(player->movement.blocked));
		for (int i = 0; map && map[i].layer; i++) {
			if (map[i].solid) {
				if (player->movement.pos.y + 31 + player->movement.speed >= map[i].pos.y && player->movement.pos.y + 17 <= map[i].pos.y && player->movement.pos.x < map[i].pos.x + 16 && player->movement.pos.x + 16 > map[i].pos.x)
					player->movement.blocked.down = true;
				if (player->movement.pos.y + 16 + player->movement.speed >= map[i].pos.y && player->movement.pos.y - 1 <= map[i].pos.y && player->movement.pos.x + 1 <= map[i].pos.x + 16 && map[i].pos.x <= player->movement.pos.x + 15)
					player->movement.blocked.up = true;
				if (player->movement.pos.y + 29 >= map[i].pos.y - 1 && player->movement.pos.y + 17 <= map[i].pos.y + 16 && player->movement.pos.x <= map[i].pos.x + 16 + player->movement.speed && map[i].pos.x <= player->movement.pos.x)
					player->movement.blocked.left = true;
				if (player->movement.pos.y + 29 >= map[i].pos.y - 1 && player->movement.pos.y + 17 <= map[i].pos.y + 16 && player->movement.pos.x <= map[i].pos.x && player->movement.pos.x + 16 + player->movement.speed >= map[i].pos.x)
					player->movement.blocked.right = true;
			}
			if (player->movement.pos.y + 30 >= map[i].pos.y && player->movement.pos.y <= map[i].pos.y && player->movement.pos.x - 16 < map[i].pos.x && player->movement.pos.x + 16 > map[i].pos.x)
				execAction(game, map[i]);
		}
		player->movement.speed = 0;
		if (!player->movement.blocked.left && isPressed(game->settings.keys[KEY_LEFT], game->window)) {
			player->movement.pos.x -= isPressed(game->settings.keys[KEY_LEFT], game->window);
			if (isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window))
				player->movement.position = LEFT;
			player->movement.state = isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window);
			if (isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game->settings.keys[KEY_SPRINT], game->window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.x -= player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window)) - 1;
				if (!mooved && isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window)) - 1;
				if (isPressed(game->settings.keys[KEY_LEFT], game->window) - isPressed(game->settings.keys[KEY_RIGHT], game->window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
		if (!player->movement.blocked.right && isPressed(game->settings.keys[KEY_RIGHT], game->window)) {
			player->movement.pos.x += isPressed(game->settings.keys[KEY_RIGHT], game->window);
			if (isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window))
				player->movement.position = RIGHT;
			player->movement.state = isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window);
			if (isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game->settings.keys[KEY_SPRINT], game->window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.x += player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window)) - 1;
				if (!mooved && isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window)) - 1;
				if (isPressed(game->settings.keys[KEY_RIGHT], game->window) - isPressed(game->settings.keys[KEY_LEFT], game->window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
		if (!player->movement.blocked.up && isPressed(game->settings.keys[KEY_UP], game->window)) {
			player->movement.pos.y -= isPressed(game->settings.keys[KEY_UP], game->window);
			if (isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window))
				player->movement.position = UP;
			player->movement.state = isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window);
			if (isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game->settings.keys[KEY_SPRINT], game->window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.y -= player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window)) - 1;
				if (!mooved && isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window)) - 1;
				if (isPressed(game->settings.keys[KEY_UP], game->window) - isPressed(game->settings.keys[KEY_DOWN], game->window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
		if (!player->movement.blocked.down && isPressed(game->settings.keys[KEY_DOWN], game->window)) {
			player->movement.pos.y += isPressed(game->settings.keys[KEY_DOWN], game->window);
			if (isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window))
				player->movement.position = DOWN;
			player->movement.state = isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window);
			if (isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game->settings.keys[KEY_SPRINT], game->window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.y += player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window)) - 1;
				if (!mooved && isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window)) - 1;
				if (isPressed(game->settings.keys[KEY_DOWN], game->window) - isPressed(game->settings.keys[KEY_UP], game->window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
	}
	while (player->stats.energyClock >= player->stats.timeBeforeEnergyUse && player->stats.timeBeforeEnergyUse) {
		player->stats.energyClock -= player->stats.timeBeforeEnergyUse;
		player->stats.energy -= player->stats.energyUsedBySprint;
		sfClock_restart(player->stats.energyRegenClock);
	}
	if (sfTime_asSeconds(sfClock_getElapsedTime(player->stats.energyRegenClock)) >= 4)
		player->stats.energy += player->stats.energyRegen;
	if (player->stats.energy > player->stats.maxEnergy * 10)
		player->stats.energy = player->stats.maxEnergy * 10;
}

void	inGame(game_t *game)
{
	Character	*player = getPlayer(game->characters.content, game->characters.length);
	char		*tmp = NULL;
	static int	color = 255;

	displayLowerLayer(game);
	displayCharacters(game);
	displayUpperLayer(game);
	displayHUD(game);
	if (player->movement.speed < 0)
		player->movement.speed = 0;
	if (game->debug) {
		sfText_setCharacterSize(game->text, 10);
		tmp = concatf("X: %f\nY: %f\ncamX: %i\ncamY: %i\n", player->movement.pos.x, player->movement.pos.y, game->cam.x, game->cam.y);
		sfText_setColor(game->text, (sfColor){abs(color), abs(color), abs(color), 255});
		text(tmp, game, 0, game->settings.dispFramerate ? 10 : 0, false);
		free(tmp);
		color--;
		if (color < -255)
			color *= -1;
	}
	movePlayer(game);
	for (int i = 0; i < game->characters.length; i++) {
		Character	*chara = &((Character *)game->characters.content)[i];

		if (chara->stats.life > 10 * chara->stats.lifeMax)
			chara->stats.life = 10 * chara->stats.lifeMax;
		chara->invulnerabiltyTime -= chara->invulnerabiltyTime > 0 ? 1 : 0;
	}
}
