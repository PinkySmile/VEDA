#include <math.h>
#include "character.h"

double	getResistances(Character *character, int damageType)
{
	double	res = 0;

	for (int i = 0; i < 5; i++)
		if (character->wornItems[i].name) {
			res += character->wornItems[i].resistances[damageType];
			if (character->wornItems[i].resistances[damageType] > 0) {
				if (character->wornItems[i].durability <= 0)
					character->wornItems[i].name = NULL;
				for (int j = 0; character->wornItems[i].name != NULL && j < DAMAGES_TYPE_NB; j++)
					character->wornItems[i].resistances[j] = character->wornItems[i].baseResistances[j] * character->wornItems[i].durability / character->wornItems[i].baseDurability;
			}
		}
	return res;
}

void	dealDamages(Character *character, int damages, int damageType)
{
	float	buffer = character->stats.life;
	double	res = 0;

	if (damageType != TRUE_DAMAGE) {
		res = getResistances(character, damageType);
		for (int i = 0; i < 5; i++)
			character->wornItems[i].durability -= damages / 10.;
		character->stats.life -= damages * (20 / (sqrt(res) + 20));
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