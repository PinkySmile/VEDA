#include <SFML/Graphics.h>
#include <lua.h>
#include <malloc.h>
#include "battle.h"
#include "projectile.h"

void	destroyBattle(Battle battle)
{
	if (battle.lua)
		lua_close(battle.lua);
	sfClock_destroy(battle.clock);
	free(battle.script);
	free(battle.name);
	for (int j = 0; j < DAMAGES_TYPE_NB; j++)
		sfClock_destroy(battle.boss.damageClock[j]);
	if (battle.bossSprite.sprite && battle.needToDestroySprite) {
		sfSprite_destroy(battle.bossSprite.sprite);
		sfTexture_destroy(battle.bossSprite.texture);
	}
	for (int i = 0; i < battle.projectileBank.length; i++) {
		Projectile	*proj = &((Projectile *)battle.projectileBank.content)[i];

		if (proj->needToDestroySprite) {
			sfSprite_destroy(proj->sprite.sprite);
			sfTexture_destroy(proj->sprite.texture);
		}
	}
	free(battle.projectileBank.content);
	battle.projectileBank.length = 0;
	if (battle.music && battle.needToDestroyMusic) {
		sfMusic_stop(battle.music);
		sfMusic_destroy(battle.music);
	}
}
