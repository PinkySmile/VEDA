#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "macros.h"
#include "character.h"
#include "object.h"

void	moveCharacter(Character *character, sfVector2f direction)
{
	Object		*map = game.state.loadedMap.objects;
	float		animationSeconds = sfTime_asSeconds(sfClock_getElapsedTime(character->movement.animationClock));
	float		stateSeconds = sfTime_asSeconds(sfClock_getElapsedTime(character->movement.stateClock));
	sfVector2f	pos = character->movement.pos;
	sfVector2f	distance;

	if (character->movement.state == MOVING && animationSeconds >= 0.1 / character->movement.speed) {
		character->movement.animation = !character->movement.animation;
		if (getMusic(character->stepSound))
			sfMusic_play(getMusic(character->stepSound));
		sfClock_restart(character->movement.animationClock);
	} else if (character->movement.state == MOVING && stateSeconds >= 0.3) {
		character->movement.state = STATIC;
		character->movement.animation = 0;
	}
	character->stepSound = IRON;
	if (character->movement.canMove) {
		memset(&character->movement.blocked, 0, sizeof(character->movement.blocked));
		for (int i = 0; map && map[i].layer; i++) {
			if (map[i].solid) {
				distance.x = map[i].pos.x - pos.x;
				distance.y = map[i].pos.y - pos.y;
				if (
					distance.x > PLAYER_HITBOX_OFFSET.x + PLAYER_HITBOX_SIZE.x &&
					distance.x < character->movement.blocked.right &&
					map[i].pos.y + OBJECT_SIZE.y > pos.x + PLAYER_HITBOX_OFFSET.y &&
					map[i].pos.y < pos.y + PLAYER_HITBOX_OFFSET.y + PLAYER_HITBOX_SIZE.y
				)
					character->movement.blocked.right = abs(distance.x);

				else if (
					distance.x < PLAYER_HITBOX_OFFSET.x &&
					distance.x < character->movement.blocked.left
				)
					character->movement.blocked.left = abs(distance.x);

				if (
					distance.y > PLAYER_HITBOX_OFFSET.y + PLAYER_HITBOX_SIZE.y &&
					distance.y < character->movement.blocked.down
				)
					character->movement.blocked.down = abs(distance.y);

				else if (
					distance.y < PLAYER_HITBOX_OFFSET.y &&
					distance.y < character->movement.blocked.up
				)
					character->movement.blocked.up = abs(distance.y);
			}
		}
		character->movement.speed = 0;
		if (direction.x > 0) {
			character->movement.pos.x += direction.x;
			character->movement.state = MOVING;
			character->movement.position = RIGHT;
		}
		if (direction.x < 0) {
			character->movement.pos.x += direction.x;
			character->movement.state = MOVING;
			character->movement.position = LEFT;
		}
		if (direction.y > 0) {
			character->movement.pos.y += direction.y;
			character->movement.state = MOVING;
			character->movement.position = DOWN;
		}
		if (direction.y < 0) {
			character->movement.pos.y += direction.y;
			character->movement.state = MOVING;
			character->movement.position = UP;
		}
	}
}