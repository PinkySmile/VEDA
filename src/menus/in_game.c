#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "display.h"
#include "graphic.h"
#include "utils.h"

void	displayLowerLayer()
{
	Object		*map = game.state.loadedMap.objects;
	Array		sprites = game.ressources.sprites;
	sfVector2i	cam = game.state.cameraPos;
	sfIntRect	rec = {0, 0, 16, 16};
	char		*buffer = NULL;

	for (int i = 0; map && map[i].layer; i++) {
		if (map[i].layer == 1 && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			if (!((Sprite *)sprites.content)[OBJECTS].sprite) {
				sfRectangleShape_setOutlineColor(game.ressources.rectangle, (sfColor){0, 0, 0, 0});
				sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){((map[i].id * 10) >> 16) * 20 % 256, ((map[i].id * 10) >> 8) * 10 % 256, map[i].id * 10 % 256, 255});
				rect(map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
			} else {
				rec.left = (map[i].id - 1) * 16 % 640;
				rec.top = (map[i].id - 1) * 16 / 640;
				sfSprite_setTextureRect(((Sprite *)sprites.content)[OBJECTS].sprite, rec);
				image(((Sprite *)sprites.content)[OBJECTS].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
			}
			if (game.debug) {
				sfText_setCharacterSize(game.ressources.text, 15);
				sfText_setColor(game.ressources.text, (sfColor){0, 0, 0, 200});
				buffer = concatf("%i", map[i].id);
				text(buffer, map[i].pos.x + cam.x, map[i].pos.y + cam.y, false);
				free(buffer);
			}
		}
	}
}

void	displayCharacter(Character *character, int id, sfSprite *sprite)
{
	sfIntRect	rec = {0, 0, 16, 32};
	sfVector2i	cam = game.state.cameraPos;

	//Check if the character is out of the screen
	if (character->movement.pos.x + cam.x < -16)
		return;
	if (character->movement.pos.y + cam.y < -32)
		return;
	if (character->movement.pos.x + cam.x > 640)
		return;
	if (character->movement.pos.y + cam.y > 480)
		return;

	//Select the good animation
	rec.top = (character->movement.position / 2 + (character->movement.state * 2) + (character->movement.animation * 2)) * 32;
	rec.left = (character->movement.position % 2) * 32;

	//Display the sprite
	if (sprite) {
		sfSprite_setTextureRect(sprite, rec);
		image(sprite, character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 16, 32);
	} else {
		sfRectangleShape_setOutlineColor(game.ressources.rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){id * 2 % 256, ((id * 10) >> 8) * 10 % 256, id * 2 % 256, 255});
		rect(character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 16, 32);
	}
}

void	displayCharacters()
{
	Character	buff;
	static int	var = 0;

	for (int i = 0; i < game.state.characters.length; i++) {
		buff = ((Character *)game.state.characters.content)[i];
		if (getSprite(MALE_CHARACTER + buff.texture) && (!buff.invulnerabiltyTime || var % 5 <= 3))
			displayCharacter(&buff, i, getSprite(MALE_CHARACTER + buff.texture)->sprite);
	}
	var = var >= 4 ? 0 : var + 1;
}

void	displayUpperLayer()
{
	Object		*map = game.state.loadedMap.objects;
	Array		sprites = game.ressources.sprites;
	sfVector2i	cam = game.state.cameraPos;
	sfIntRect	rec = {0, 0, 16, 16};
	bool		newLayer = true;
	char		*buffer = NULL;

	for (int nextLayer, layer = 2; newLayer; layer = nextLayer) {
		newLayer = false;
		nextLayer = 0;
		for (int i = 0; map && map[i].layer; i++) {
			if (map[i].layer == layer && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
				if (!((Sprite *)sprites.content)[OBJECTS].sprite) {
					sfRectangleShape_setOutlineColor(game.ressources.rectangle, (sfColor){0, 0, 0, 0});
					sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){((map[i].id * 10) >> 16) * 20 % 256, ((map[i].id * 10) >> 8) * 10 % 256, map[i].id * 10 % 256, 255});
					rect(map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
				} else {
					rec.left = (map[i].id - 1) * 16 % 640;
					rec.top = (map[i].id - 1) * 16 / 640;
					sfSprite_setTextureRect(((Sprite *)sprites.content)[OBJECTS].sprite, rec);
					image(((Sprite *)sprites.content)[OBJECTS].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
				}
				if (game.debug) {
					sfText_setCharacterSize(game.ressources.text, 15);
					sfText_setColor(game.ressources.text, (sfColor){layer % 2 == 0 ? 255 : 0, layer % 3 == 0 ? 255 : 0, layer % 4 == 0 ? 255 : 0, 200});
					buffer = concatf("%i", map[i].id);
					text(buffer, map[i].pos.x + cam.x, map[i].pos.y + cam.y, false);
					free(buffer);
				}
			}
			nextLayer = map[i].layer > layer && (map[i].layer < nextLayer || nextLayer == 0) ? map[i].layer : nextLayer;
			newLayer = newLayer || map[i].layer > layer;
		}
	}
	for (int i = 0; game.debug && map && map[i].layer; i++) {
		if (map[i].solid && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){255, 0, 255, 125});
			rect(map[i].pos.x + cam.x + 1, map[i].pos.y + cam.y + 1, 14, 14);
		}
		if (((Sprite *)sprites.content)[MUSICS].sprite && map[i].action == CHANGE_MUSIC && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672)
			image(((Sprite *)sprites.content)[MUSICS].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
		else if (((Sprite *)sprites.content)[CROSS].sprite && map[i].action == DEAL_DAMAGES && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672) {
			sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){0, 0, 255, 155});
			rect(map[i].pos.x + cam.x + 3, map[i].pos.y + cam.y + 3, 10, 10);
		} else if (((Sprite *)sprites.content)[CUTSCENE].sprite && map[i].action == LAUNCH_CUTSCENE && map[i].pos.x + cam.x > -32 && map[i].pos.x + cam.x < 672 && map[i].pos.y + cam.y > -32 && map[i].pos.y + cam.y < 672)
			image(((Sprite *)sprites.content)[CUTSCENE].sprite, map[i].pos.x + cam.x, map[i].pos.y + cam.y, 16, 16);
	}
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

void	execAction(Object obj)
{
	Character	*player = getPlayer(game.state.characters.content, game.state.characters.length);

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
	if (obj.footstepSound > player->stepSound)
		player->stepSound = obj.footstepSound + rand() % obj.footstepVariance;
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

void	movePlayer()
{
	Character	*player = getPlayer(game.state.characters.content, game.state.characters.length);
	Object		*map = game.state.loadedMap.objects;
	bool		mooved = false;

	if (player->movement.pos.x + game.state.cameraPos.x + 8 > 640) {
		game.state.cameraPos.x -= 640;
	} else if (player->movement.pos.x + game.state.cameraPos.x + 8 < 0) {
		game.state.cameraPos.x += 640;
	} else if (player->movement.pos.y + game.state.cameraPos.y + 16 > 480) {
		game.state.cameraPos.y -= 480;
	} else if (player->movement.pos.y + game.state.cameraPos.y + 16 < 0) {
		game.state.cameraPos.y += 480;
	}
	if (player->movement.state == MOVING && sfTime_asSeconds(sfClock_getElapsedTime(player->movement.animationClock)) >= 0.1 / player->movement.speed) {
		player->movement.animation = !player->movement.animation;
		if (((sfMusic **)game.ressources.sfx.content)[player->stepSound])
			sfMusic_play(((sfMusic **)game.ressources.sfx.content)[player->stepSound]);
		sfClock_restart(player->movement.animationClock);
	} else if (player->movement.state == MOVING && sfTime_asSeconds(sfClock_getElapsedTime(player->movement.stateClock)) >= 0.3) {
		player->movement.state = STATIC;
		player->movement.animation = 0;
	}
	player->stepSound = IRON;
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
				execAction(map[i]);
		}
		player->movement.speed = 0;
		if (!player->movement.blocked.left && isPressed(game.settings.keys[KEY_LEFT], game.ressources.window)) {
			player->movement.pos.x -= isPressed(game.settings.keys[KEY_LEFT], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window))
				player->movement.position = LEFT;
			player->movement.state = isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game.settings.keys[KEY_SPRINT], game.ressources.window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.x -= player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window)) - 1;
				if (!mooved && isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window)) - 1;
				if (isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) - isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
		if (!player->movement.blocked.right && isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window)) {
			player->movement.pos.x += isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window))
				player->movement.position = RIGHT;
			player->movement.state = isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game.settings.keys[KEY_SPRINT], game.ressources.window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.x += player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window)) - 1;
				if (!mooved && isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window)) - 1;
				if (isPressed(game.settings.keys[KEY_RIGHT], game.ressources.window) - isPressed(game.settings.keys[KEY_LEFT], game.ressources.window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
		if (!player->movement.blocked.up && isPressed(game.settings.keys[KEY_UP], game.ressources.window)) {
			player->movement.pos.y -= isPressed(game.settings.keys[KEY_UP], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window))
				player->movement.position = UP;
			player->movement.state = isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game.settings.keys[KEY_SPRINT], game.ressources.window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.y -= player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window)) - 1;
				if (!mooved && isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window)) - 1;
				if (isPressed(game.settings.keys[KEY_UP], game.ressources.window) - isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) != 0)
					player->stats.energyClock++;
			}
			mooved = player->movement.speed != 0;
		}
		if (!player->movement.blocked.down && isPressed(game.settings.keys[KEY_DOWN], game.ressources.window)) {
			player->movement.pos.y += isPressed(game.settings.keys[KEY_DOWN], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window))
				player->movement.position = DOWN;
			player->movement.state = isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window) ? MOVING : player->movement.state;
			if (!mooved)
				player->movement.speed += isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window);
			if (isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window))
				sfClock_restart(player->movement.stateClock);
			if (isPressed(game.settings.keys[KEY_SPRINT], game.ressources.window) && player->stats.energy >= player->stats.sprintSpeed) {
				player->movement.pos.y += player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window)) - 1;
				if (!mooved && isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window))
					player->movement.speed += player->stats.sprintSpeed * (isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window)) - 1;
				if (isPressed(game.settings.keys[KEY_DOWN], game.ressources.window) - isPressed(game.settings.keys[KEY_UP], game.ressources.window) != 0)
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

bool	addCharacter(char c, char **str)
{
	int	start = 0;
	char	*buffer = str ? *str : NULL;
	
	if (!buffer) {
		buffer = malloc(2);
		if (!buffer)
			return (false);
		*str = buffer;
		buffer[0] = c;
		buffer[1] = 0;
		return (true);
	}
	buffer = realloc(buffer, strlen(buffer) + 2);
	if (!buffer)
		return (false);
	for (int i = 0; buffer[i]; i++)
		if (buffer[i] == '\n')
			start = i + 1;
	if (strlen(buffer) - start > 78) {
		for (int i = strlen(buffer) - 1; i >= 0; i--)
			if (buffer[i] == ' ' || buffer[i] == '\t') {
				buffer[i] = '\n';
				break;
			} else if (buffer[i] == '\n')
				break;
	}
	buffer[strlen(buffer) + 1] = 0;
	buffer[strlen(buffer)] = c;
	*str = buffer;
	return (true);
}

bool	addStringToDialogBox(char *str, char **resulting)
{
	if (!str)
		return (addStringToDialogBox("(null)", resulting));
	for (int i = 0; str[i]; i++)
		if (!addCharacter(str[i], resulting))
			return (false);
	return (true);
}

void	resolveCommand(DialogDisplayed *diag)
{
	char	*command = &diag->rawText[diag->index + 1];
	char	*result;

	for (diag->index++; diag->rawText[diag->index] && diag->rawText[diag->index] != '%'; diag->index++);
	if (!diag->rawText[diag->index]) {
		addStringToDialogBox("Unfinished command found", &diag->displayedText);
		return;
	}
	diag->rawText[diag->index] = 0;
	result = executeCommand(command, NULL);
	if (result)
		addStringToDialogBox(result, &diag->displayedText);
	free(result);
	diag->rawText[diag->index] = '%';
	diag->index++;
}

void	displayDialogs()
{
	for (int i = 0; i < game.state.dialogs; i++) {
		if (!game.state.dialogsOnScreen[i].displayedText)
			game.state.dialogsOnScreen[i].displayedText = concatf("%s: ", game.state.dialogsOnScreen[i].dialogOwnerName);
		sfText_setCharacterSize(game.ressources.text, 15);
		sfText_setColor(game.ressources.text, (sfColor){255, 255, 255, 255});
		text(game.state.dialogsOnScreen[i].displayedText, 10, 390, false);
		if (game.state.dialogsOnScreen[i].index < (int)strlen(game.state.dialogsOnScreen[i].rawText) - 1 && sfTime_asSeconds(sfClock_getElapsedTime(game.state.dialogsOnScreen[i].clock)) > game.state.dialogsOnScreen[i].speed) {
			if (game.state.dialogsOnScreen[i].rawText[game.state.dialogsOnScreen[i].index] == '%')
				resolveCommand(&game.state.dialogsOnScreen[i]);
			else
				addCharacter(game.state.dialogsOnScreen[i].rawText[game.state.dialogsOnScreen[i].index++], &game.state.dialogsOnScreen[i].displayedText);
			sfClock_restart(game.state.dialogsOnScreen[i].clock);
		}
	}
}

void	inGame()
{
	Character	*player = getPlayer(game.state.characters.content, game.state.characters.length);
	char		*tmp = NULL;
	static int	color = 255;

	displayLowerLayer();
	displayCharacters();
	displayUpperLayer();
	displayHUD();
	if (player->movement.speed < 0)
		player->movement.speed = 0;
	if (game.debug) {
		sfText_setCharacterSize(game.ressources.text, 10);
		tmp = concatf("X: %f\nY: %f\ncamX: %i\ncamY: %i\n", player->movement.pos.x, player->movement.pos.y, game.state.cameraPos.x, game.state.cameraPos.y);
		sfText_setColor(game.ressources.text, (sfColor){abs(color), abs(color), abs(color), 255});
		text(tmp, 0, game.settings.dispFramerate ? 10 : 0, false);
		free(tmp);
		color--;
		if (color < -255)
			color *= -1;
	}
	movePlayer();
	if (game.state.dialogs) {
		image(((Sprite *)game.ressources.sprites.content)[DIALOG_BOX].sprite, 0, 380, 640, 100);
		displayDialogs();
	}
	for (int i = 0; i < game.state.characters.length; i++) {
		Character	*chara = &((Character *)game.state.characters.content)[i];

		if (chara->stats.life > 10 * chara->stats.lifeMax)
			chara->stats.life = 10 * chara->stats.lifeMax;
		chara->invulnerabiltyTime -= chara->invulnerabiltyTime > 0 ? 1 : 0;
	}
}
