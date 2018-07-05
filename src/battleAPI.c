#include <stdbool.h>
#include <malloc.h>
#include "structs.h"

extern	game_t	game;

bool	addProjectile(int id, int x, int y)
{
	void		*buff;
	Projectile	*projs = game.battle_infos.projectiles.content;
	Projectile	*bank = game.battle_infos.projectileBank.content;
	
	game.battle_infos.projectiles.length++;
	buff = realloc(game.battle_infos.projectiles.content, game.battle_infos.projectiles.length * sizeof(Projectile));
	if (id < 0)
		return false;
	if (id >= game.battle_infos.projectileBank.length)
		return false;
	if (!buff)
		return false;
	game.battle_infos.projectiles.content = buff;
	projs = buff;
	projs[game.battle_infos.projectiles.length - 1] = bank[id];
	projs[game.battle_infos.projectiles.length - 1].pos.x = x;
	projs[game.battle_infos.projectiles.length - 1].pos.y = y;
	projs[game.battle_infos.projectiles.length - 1].clock = sfClock_create();
	projs[game.battle_infos.projectiles.length - 1].animClock = sfClock_create();
	return true;
}