#ifndef __BATTLE_API_H_
#define __BATTLE_API_H_

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "character.h"
#include "data_structures/projectile.h"

//Lua functions
int	addProjectileLua	(lua_State *Lua);
int	playSoundLua		(lua_State *Lua);
int	getElapsedTime		(lua_State *Lua);
int	stopTime		(lua_State *Lua);
int	yield			(lua_State *Lua);
int	destroyProjectile	(lua_State *Lua);
int	getProjectileField	(lua_State *Lua);
int	setProjectileField	(lua_State *Lua);
int	getCharacterField	(lua_State *Lua);
int	setCharacterField	(lua_State *Lua);
int	char2string		(lua_State *Lua);

//Utils functions
void		pushCharacter	(lua_State *Lua, Character *character);
void		pushProjectile	(Projectile *proj, lua_State *Lua);
void		addDependencies	(lua_State *Lua);
int		playSound	(char const *path, bool freeAll);
Projectile	*addProjectile	(int id, int x, int y, int ownerID, float angle, float speed, float rotaSpeed, float accel, int marker);

#endif
