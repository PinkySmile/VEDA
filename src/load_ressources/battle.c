#include <structs.h>
#include <stdio.h>
#include <concatf.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <loading.h>
#include <battle_lua.h>
#include <setjmp.h>
#include <context.h>

Battle	loadBattleScript(char *path)
{
	Battle		battle = game.state.battle_infos;
	int		err;
	ParserResult	result = Parser_parseFile(path, NULL);
	char		*buffer;
	Context		context;

	memset(&context, 0, sizeof(context));
	printf("%s: Loading %s as battle infos\n", INFO_BEG, path);

	battle.type = BATTLE_ERROR;
	if (result.error) {
		printf("%s: %s\n", ERROR_BEG, result.error);
		result.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, result.error);
		dispMsg("Battle Error", result.error, 0);
		free(result.error);
		return battle;
	} else if (result.type != ParserObjType) {
		Parser_destroyData(result.data, result.type);
		memset(&battle, 0, sizeof(battle));
		printf("%s: %s: Invalid type found in the file\n", ERROR_BEG, path);
		buffer = concatf("Error: %s: Invalid type found in the file\n", path);
		dispMsg("Battle Error", buffer, 0);
		free(buffer);
		return battle;
	}

	if (setjmp(context.jumpBuffer)) {
		Parser_destroyData(result.data, result.type);
		printf("%s: %s: %s\n", ERROR_BEG, path, context.error);
		buffer = concatf(
			"Error: File '%s' contains invalid battle data:\n%s\n",
			path,
			context.error
		);
		dispMsg("Battle Error", buffer, 0);
		free(buffer);
		Parser_destroyData(result.data, result.type);
		return battle;
	}

	context.onMissing = DISPLAY_WARNING;
	context.onInvalidType = LONG_JUMP;
	context.onUseFail = LONG_JUMP;
	context.object = result.data;

	context.data = &battle.type;
	context.index = "type";
	context.useElement = getBattleType;
	context.expectedType = ContextIntType | ContextStringType;
	getObjectElement(&context);

	context.data = &battle.name;
	context.index = "battle_name";
	context.useElement = getDuppedString;
	context.expectedType = ContextStringType;
	getObjectElement(&context);

	context.data = battle.boss.name;
	context.index = "boss_name";
	context.useElement = copyStringInBuffer;
	context.expectedType = ContextStringType;
	getObjectElement(&context);

	context.data = &battle.bossSprite;
	context.index = "boss_sprite_sheet";
	context.useElement = loadSprite;
	context.expectedType = ContextIntType | ContextStringType;
	getObjectElement(&context);

	context.data = &battle.projectileBank;
	context.index = "projectiles";
	context.useElement = loadProjectilesScript;
	context.expectedType = ContextStringType;
	getObjectElement(&context);

	context.data = &battle;
	context.index = "base_script";
	context.useElement = loadBattleLuaScript;
	context.expectedType = ContextStringType;
	getObjectElement(&context);

	context.data = &battle.music;
	context.index = "music";
	context.useElement = loadMusic;
	context.expectedType = ContextIntType | ContextStringType;
	getObjectElement(&context);

	context.data = &battle.bossSprite.rect.width;
	context.index = "boss_sprite_size";
	context.useElement = getUintVector;
	context.expectedType = ContextObjType;
	getObjectElement(&context);

	context.data = &battle.bossHitbox;
	context.index = "boss_hitbox";
	context.useElement = getUintVector;
	context.expectedType = ContextObjType;
	getObjectElement(&context);

	context.data = &battle.playerHitbox;
	context.index = "player_hitbox";
	context.useElement = getUintVector;
	context.expectedType = ContextObjType;
	getObjectElement(&context);

	ParserObj_destroy(result.data);
	for (int j = 0; j < DAMAGES_TYPE_NB; j++)
		battle.boss.damageClock[j] = sfClock_create();
	battle.clock = sfClock_create();
	return battle;
}
