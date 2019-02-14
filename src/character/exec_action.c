#include "object.h"
#include "character.h"
#include "utils.h"

void	execAction(Object obj, Character *character)
{
	//If the character is not on the object, return
	if (!(
		character->movement.pos.x + PLAYER_HITBOX_OFFSET.x + PLAYER_HITBOX_SIZE.x < obj.pos.x + 1 ||
		character->movement.pos.y + PLAYER_HITBOX_OFFSET.y + PLAYER_HITBOX_SIZE.y < obj.pos.y + 1 ||
		character->movement.pos.x + PLAYER_HITBOX_OFFSET.x > obj.pos.x + OBJECT_SIZE.x ||
		character->movement.pos.y + PLAYER_HITBOX_OFFSET.y > obj.pos.y + OBJECT_SIZE.y
	)) {
		if (obj.solid) {
			switch (character->movement.position) {
			case LEFT:
				character->movement.pos.x = obj.pos.x - PLAYER_HITBOX_OFFSET.x + OBJECT_SIZE.x + 1;
				break;
			case RIGHT:
				character->movement.pos.x = obj.pos.x - PLAYER_HITBOX_OFFSET.x - PLAYER_HITBOX_SIZE.x;
				break;
			case UP:
				character->movement.pos.y = obj.pos.y - PLAYER_HITBOX_OFFSET.y + OBJECT_SIZE.y + 1;
				break;
			case DOWN:
				character->movement.pos.y = obj.pos.y - PLAYER_HITBOX_OFFSET.y - PLAYER_HITBOX_SIZE.y;
				break;
			}
			character->movement.state = STATIC;
			character->movement.animation = 0;
		}

		if (obj.footstepSound > character->stepSound)
			character->stepSound = obj.footstepSound + random() % obj.footstepVariance;
		switch (obj.action) {
		case DEAL_DAMAGES:
			for (int i = 0; i < DAMAGES_TYPE_NB; i++) {
				if (obj.damages[i] && (character->invulnerabiltyTime <= 0 || obj.damages[i] < 0)) {
					dealDamages(character, obj.damages[i], i);
					character->invulnerabiltyTime = obj.invulnerabiltyTime;
				}
			}
			break;
		case CHANGE_MUSIC:
			break;
		case LAUNCH_CUTSCENE:
			break;
		}
	}
}
