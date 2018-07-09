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

bool	addProjectile(int id, int x, int y, int ownerID, float angle)
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
	double	x = luaL_checknumber(Lua, 1);
	double	y = luaL_checknumber(Lua, 2);
	double	projID = luaL_checknumber(Lua, 3);
	double	ownerID = luaL_checknumber(Lua, 4);
	double	angle = luaL_checknumber(Lua, 5);

	if (projID >= game.battle_infos.projectileBank.length || projID < 0)
		luaL_error(Lua, "No projectile exists with id %i", projID);
	addProjectile(projID, x, y, ownerID, angle);
	return 0;
}

int	yield(lua_State *Lua)
{
	//This is temporary, I didn't find better ways to do it yet
	static int	loopCount = 0;
	static int	oldTime = 0;
	static char	frameRate[30];
	char		*buffer;
	int		frames = 1;


	if (!lua_isnumber(Lua, 1) && !lua_isnone(Lua, 1))
		luaL_error(Lua, "Invalid argument #1 for function 'yield': Expected number or no value");
	else if (lua_isnumber(Lua, 1)) {
		if (lua_tonumber(Lua, 1) >= 1)
			frames = lua_tonumber(Lua, 1);
		else
			luaL_error(Lua, "Invalid argument #1 for function 'yield': Positive and not null number expected (got %d)", lua_tonumber(Lua, 1));
	}
	for (int i = 0; i < frames && game.menu == 7 && sfRenderWindow_isOpen(game.window); i++) {
		if (game.menu == 7 && sfRenderWindow_isOpen(game.window)) {
			sfRenderWindow_clear(game.window, (sfColor){0, 0, 0, 255});
			game_functions[game.menu](&game);
			disp_buttons(&game);
			manageEvents(&game);
			loopCount++;
			if (oldTime != time(NULL)) {
				buffer = concatf("%f FPS", (float)loopCount / (time(NULL) - oldTime));
				strcpy(frameRate, buffer);
				free(buffer);
				loopCount = 0;
				oldTime = time(NULL);
			}
			if (game.settings.dispFramerate) {
				sfText_setCharacterSize(game.text, 10);
				sfText_setColor(game.text, (sfColor){255, 255, 255, 255});
				text(frameRate, &game, 2, 0, false);
			}
			if (game.debug) {
				sfText_setCharacterSize(game.text, 10);
				sfText_setColor(game.text, (sfColor){255, 255, 255, 255});
				text("Debug mode", &game, 580, 0, false);
				sfText_setColor(game.text, (sfColor){0, 0, 0, 255});
			}
			sfRenderWindow_display(game.window);
		} else {
			if (game.menu == 7)
				game.menu = 0;
		}
	}
	if (game.menu == 7 && sfRenderWindow_isOpen(game.window))
		lua_pushboolean(Lua, 1);
	else
		lua_pushboolean(Lua, 0);
	return 1;
}
