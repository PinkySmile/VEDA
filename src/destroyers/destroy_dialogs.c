#include <lua.h>
#include "structs.h"

void	destroyDialogs()
{
	if (game.ressources.dialogLuaScript)
		lua_close(game.ressources.dialogLuaScript);
}