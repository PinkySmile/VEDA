#include "functions.h"
#include "concatf.h"
#include "structs.h"
#include "configParser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Battle	loadBattleScript(char *path)
{
	Battle		battle;
	ParserResult	file = Parser_parseFile(path, NULL);

	memset(&battle, 0, sizeof(battle));
	if (file.error) {
		printf("%s: %s\n", ERROR, file.error);
		file.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, file.error);
		dispMsg("Battle Error", file.error, 0);
		free(file.error);
		return battle;
	}
	return battle;
}

void	battle(game_t *game)
{

}
