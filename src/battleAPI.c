#include <stdbool.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include "structs.h"
#include "functions.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "concatf.h"

extern	game_t	game;
extern	void	(* const game_functions[])(game_t *game);

bool	addProjectile(int id, int x, int y, int ownerID, float angle, float speed, float rotaSpeed, float accel, int marker)
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
	projs[game.battle_infos.projectiles.length - 1].owner = ownerID;
	projs[game.battle_infos.projectiles.length - 1].angle = angle;
	projs[game.battle_infos.projectiles.length - 1].marker = marker;
	if (speed)
		projs[game.battle_infos.projectiles.length - 1].speed = speed;
	if (rotaSpeed)
		projs[game.battle_infos.projectiles.length - 1].rotaSpeed = rotaSpeed;
	if (accel)
		projs[game.battle_infos.projectiles.length - 1].acceleration = accel;
	return true;
}

void	destroyProjectile(int index)
{
	void		*buff;
	Projectile	*projs = game.battle_infos.projectiles.content;

	sfClock_destroy(projs[index].clock);
	sfClock_destroy(projs[index].animClock);
	if (game.battle_infos.projectiles.length - 1 != index)
		projs[index] = projs[game.battle_infos.projectiles.length - 1];
	game.battle_infos.projectiles.length--;
	buff = realloc(game.battle_infos.projectiles.content, game.battle_infos.projectiles.length * sizeof(Projectile));
	if (buff)
		game.battle_infos.projectiles.content = buff;
}

int	stopTime(lua_State *Lua)
{
	if (!lua_isboolean(Lua, 1))
		luaL_error(Lua, "Invalid argument #1 to 'stopTime': Expected boolean, got %s", lua_typename(Lua, lua_type(Lua, 1)));
	game.battle_infos.timeStopped = lua_toboolean(Lua, 1);
	return 0;
}

int	getElapsedTime(lua_State *Lua)
{
	lua_pushnumber(Lua, sfTime_asSeconds(sfClock_getElapsedTime(game.battle_infos.clock)));
	return 1;
}

int	c_swap(lua_State *Lua)
{
	//check and fetch the arguments
	double arg1 = luaL_checknumber(Lua, 1);
	double arg2 = luaL_checknumber(Lua, 2);

	//push the results
	lua_pushnumber(Lua, arg2);
	lua_pushnumber(Lua, arg1);

	//return number of results
	return 2;
}

int	addProjectileLua(lua_State *Lua)
{
	double	x		= luaL_checknumber(Lua, 1);
	double	y		= luaL_checknumber(Lua, 2);
	double	projID		= luaL_checknumber(Lua, 3);
	double	ownerID		= luaL_checknumber(Lua, 4);
	double	angle		= luaL_checknumber(Lua, 5);
	double	speed		= lua_isnone(Lua, 6) ? 0 : luaL_checknumber(Lua, 6);
	double	rotaSpeed	= lua_isnone(Lua, 7) ? 0 : luaL_checknumber(Lua, 7);
	double	accel		= lua_isnone(Lua, 8) ? 0 : luaL_checknumber(Lua, 8);
	double	marker		= lua_isnone(Lua, 9) ? 0 : luaL_checknumber(Lua, 9);

	if (projID >= game.battle_infos.projectileBank.length || projID < 0)
	        return 0;
	addProjectile(projID, x, y, ownerID, angle, speed, rotaSpeed, accel, marker);
	return 0;
}

int	yield(lua_State *Lua)
{
	int		frames = lua_isnone(Lua, 1) ? 1 : luaL_checknumber(Lua, 1);

	game.battle_infos.yieldTime = frames;
	if (frames <= 0)
		return 0;
	return lua_yield(Lua, 0);
}
