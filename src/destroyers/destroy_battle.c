#include <SFML/Graphics.h>
#include <lua.h>
#include <malloc.h>
#include "lib.h"
#include "projectile.h"

void	destroyBattle(Battle battle)
{
	list_t	*list = &battle.projectiles;

	if (battle.lua) {
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
		for (; list->next; list = list->next);
		for (; list && list->data; list = list->prev) {
			Projectile	*proj = list->data;

			sfClock_destroy(proj->clock);
			sfClock_destroy(proj->animClock);
			free(list->data);
			free(list->next);
		}
		if (battle.music && battle.needToDestroyMusic) {
			sfMusic_stop(battle.music);
			sfMusic_destroy(battle.music);
		}
		if (battle.lua)
			lua_close(battle.lua);
	}
}