#include <structs.h>
#include <graphic.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <utils.h>

void	displayDamagesTakenBy(Character *character)
{
	char		buffer[12];
	sfVector2i	cam = game.state.cameraPos;
	sfColor		color = {0, 0, 0, 255};

	for (int i = 0; i < DAMAGES_TYPE_NB; i++) {
		if (character->damageDisplay[i]) {
			float	damageBuffer = sfTime_asSeconds(sfClock_getElapsedTime(character->damageClock[i])) * 512;

			if (damageBuffer >= 255) {
				sfClock_restart(character->damageClock[i]);
				character->damageDisplay[i] = 0;
			} else {
				if (character->damageDisplay[i] < 0) {
					switch (i) {
					case TRUE_DAMAGE:
						color = (sfColor){255, 255, 255, 255 - damageBuffer / 4};
						break;
					case FIRE_DAMAGE:
						color = (sfColor){255, 205, 0, 255 - damageBuffer / 4};
						break;
					case SHARP_DAMAGE:
						color = (sfColor){0, 0, 255, 255 - damageBuffer / 4};
						break;
					case PIERCE_DAMAGE:
						color = (sfColor){255, 0, 0, 255 - damageBuffer / 4};
						break;
					case IMPACT_DAMAGE:
						color = (sfColor){170, 0, 170, 255 - damageBuffer / 4};
						break;
					case ELECTRICITY_DAMAGE:
						color = (sfColor){0, 100, 0, 255 - damageBuffer / 4};
						break;
					case POISON_DAMAGE:
						color = (sfColor){150, 100, 255, 255 - damageBuffer / 4};
					}
				} else
					color = (sfColor) {0, 255, 0, 255 - damageBuffer / 4};
				sprintf(buffer, "%i", character->damageDisplay[i]);
				sfText_setFillColor(game.resources.text, color);
				sfText_setCharacterSize(game.resources.text, 10);
				text(
					buffer,
					character->movement.pos.x + cam.x + (PLAYER_SIZE.x - getTextSize(buffer, sfText_getFont(game.resources.text), 10).x) / 2,
					character->movement.pos.y + cam.y - 10 + (
						pow(damageBuffer, 2) -
						255 * damageBuffer
					) / 1000,
					false
				);
			}
		}
	}
}
