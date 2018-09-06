#include <lua.h>

void	destroyDialogs()
{
	if (game.ressources.dialogLuaScript)
		lua_close(game.ressources.dialogLuaScript);
}