#include <string.h>
#include <malloc.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "structs.h"

extern	const	luaL_Reg	projectiles_lib[];

int	getProjectileIndex(char const *test)
{
	if (strcmp(test, "bankId") == 0)
		return (1);
	else if (strcmp(test, "x") == 0)
		return (2);
	else if (strcmp(test, "y") == 0)
		return (3);
	else if (strcmp(test, "speed") == 0)
		return (4);
	else if (strcmp(test, "acceleration") == 0)
		return (5);
	else if (strcmp(test, "owner") == 0)
		return (6);
	else if (strcmp(test, "angle") == 0)
		return (7);
	else if (strcmp(test, "rotationSpeed") == 0)
		return (8);
	else if (strcmp(test, "maxSpeed") == 0)
		return (9);
	else if (strcmp(test, "minSpeed") == 0)
		return (10);
	else if (strcmp(test, "lifeTime") == 0)
		return (11);
	return (0);
}

int	setProjectileField(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");
	int		index = lua_isnumber(lua, 2) ? luaL_checknumber(lua, 2) : getProjectileIndex(luaL_checkstring(lua, 2));

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		luaL_error(lua, "Trying to access deleted object");
	switch (index) {
		case 2:
			(*proj)->pos.x = luaL_checknumber(lua, 3);
			break;
		case 3:
			(*proj)->pos.y = luaL_checknumber(lua, 3);
			break;
		case 4:
			(*proj)->speed = luaL_checknumber(lua, 3);
			break;
		case 5:
			(*proj)->acceleration = luaL_checknumber(lua, 3);
			break;
		case 7:
			(*proj)->angle = luaL_checknumber(lua, 3);
			break;
		case 8:
			(*proj)->rotaSpeed = luaL_checknumber(lua, 3);
			break;
		default:
			luaL_error(lua, "This index is in read-only");
	}
	return (0);
}

int	getProjectileField(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");
	char	const	*ind = !lua_isnumber(lua, 2) ? luaL_checkstring(lua, 2) : NULL;
	int		index = lua_isnumber(lua, 2) ? luaL_checknumber(lua, 2) : getProjectileIndex(ind);

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		luaL_error(lua, "Trying to access deleted object");
	switch (index) {
		case 1:
			lua_pushnumber(lua, (*proj)->bankID);
			break;
		case 2:
			lua_pushnumber(lua, (*proj)->pos.x);
			break;
		case 3:
			lua_pushnumber(lua, (*proj)->pos.y);
			break;
		case 4:
			lua_pushnumber(lua, (*proj)->speed);
			break;
		case 5:
			lua_pushnumber(lua, (*proj)->acceleration);
			break;
		case 6:
			lua_pushnumber(lua, (*proj)->owner);
			break;
		case 7:
			lua_pushnumber(lua, (*proj)->angle);
			break;
		case 8:
			lua_pushnumber(lua, (*proj)->rotaSpeed);
			break;
		case 9:
			lua_pushnumber(lua, (*proj)->maxSpeed);
			break;
		case 10:
			lua_pushnumber(lua, (*proj)->minSpeed);
			break;
		case 11:
			lua_pushnumber(lua, sfTime_asSeconds(sfClock_getElapsedTime((*proj)->clock)));
			break;
		default:
			for (int i = 0; ind && projectiles_lib[i].name; i++) {
				if (strcmp(projectiles_lib[i].name, ind) == 0) {
					lua_pushcfunction(lua, projectiles_lib[i].func);
					return (1);
				}
			}
			lua_pushnil(lua);
	}
	return (1);
}

Projectile	*addProjectile(int id, int x, int y, int ownerID, float angle, float speed, float rotaSpeed, float accel, int marker)
{
	Projectile	*bank = game.state.battle_infos.projectileBank.content;
	Projectile	*proj;
	list_t		*list = &game.state.battle_infos.projectiles;

	for (; list->next && list->data; list = list->next);
	if (list->data) {
		list->next = malloc(sizeof(*list->next));
		if (!list->next)
			return (NULL);
		memset(list->next, 0, sizeof(*list->next));
		list->next->prev = list;
		list = list->next;
	}
	proj = malloc(sizeof(*proj));
	if (!proj) {
		if (list->prev) {
			list->prev->next = NULL;
			free(list);
		}
		return (NULL);
	}
	list->data = proj;
	*proj = bank[id];
	proj->pos.x = x;
	proj->pos.y = y;
	proj->clock = sfClock_create();
	proj->animClock = sfClock_create();
	proj->owner = ownerID;
	proj->angle = angle;
	proj->marker = marker;
	if (speed)
		proj->speed = speed;
	if (rotaSpeed)
		proj->rotaSpeed = rotaSpeed;
	if (accel)
		proj->acceleration = accel;
	return (proj);
}

void	pushProjectile(Projectile *proj, lua_State *lua)
{
	Projectile	**a = lua_newuserdata(lua, sizeof(proj));

	luaL_getmetatable(lua, "projectile");
	lua_setmetatable(lua, -2);
	*a = proj;
}

int	destroyProjectile(lua_State *lua)
{
	Projectile	**proj = luaL_checkudata(lua, 1, "projectile");

	luaL_argcheck(lua, proj != NULL, 1, "'projectile' expected");
	if (!*proj)
		return 0;
	printf("%s: Removing projectile\n", INFO_BEG);
	(*proj)->toRemove = true;
	*proj = NULL;
	return (0);
}

int	addProjectileLua(lua_State *lua)
{
	double		x		= luaL_checknumber(lua, 1);
	double		y		= luaL_checknumber(lua, 2);
	int		projID		= luaL_checkinteger(lua, 3);
	int		ownerID		= luaL_checkinteger(lua, 4);
	double		angle		= luaL_checknumber(lua, 5);
	double		speed		= lua_isnone(lua, 6) ? 0 : luaL_checknumber(lua, 6);
	double		rotaSpeed	= lua_isnone(lua, 7) ? 0 : luaL_checknumber(lua, 7);
	double		accel		= lua_isnone(lua, 8) ? 0 : luaL_checknumber(lua, 8);
	double		marker		= lua_isnone(lua, 9) ? 0 : luaL_checknumber(lua, 9);
	Projectile	*proj;

	if (projID >= game.state.battle_infos.projectileBank.length || projID < 0) {
		lua_pushnil(lua);
		lua_pushstring(lua, "index out of bank range");
		return 2;
	}
	proj = addProjectile(projID, x, y, ownerID, angle, speed, rotaSpeed, accel, marker);
	if (!proj)
		luaL_error(lua, "Out of memory");
	pushProjectile(proj, lua);
	return 1;
}
