#include "functions.h"
#include "concatf.h"
#include "structs.h"
#include "configParser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern game_t game;

Battle	invalidData(char *path, char *message)
{
	Battle		battle;
	char		*buffer;

	memset(&battle, 0, sizeof(battle));
	battle.type = BATTLE_ERROR;
	printf("%s: %s: %s\n", ERROR, path, message);
	buffer = concatf("Error: File '%s' contains invalid battle data:\n%s", path, message);
	dispMsg("Battle Error", buffer, 0);
	free(buffer);
	return battle;
}

Array	loadProjectiles(char *path)
{
	ParserResult	result = Parser_parseFile(path, JSON_TO_ARRAY);
	char		*buffer;
	Array		array;
	
	if (result.error) {
		printf("%s: %s\n", ERROR, result.error);
		result.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, result.error);
		dispMsg("Battle Error", result.error, 0);
		free(result.error);
		return (Array){NULL, -1};
	} else if (result.type != ParserArrayType) {
		printf("%s: %s: Invalid type\n", ERROR, path);
		buffer = concatf("Error");
		dispMsg("Battle Error", buffer, 0);
		free(buffer);
		return (Array){NULL, -1};
	}/*
	{
		"sprite_sheet": "data/battles/alexandre/battle_normal/bullets/bullet_1.png",
		"sprite_size": {
			"x": 32,
			"y": 32,
		},
		"bullet_size": {
			"x": 16,
			"y": 16,
		},
		"hitbox_size": {
			"x": 4,
			"y": 4,
		}
		"base_speed": 0,
		"base_acceleration": 10,
		"rotation_speed": 10,
		"base_angle": 0,
		"animation_speed": 10,
	}*/
	return array;
}

Battle	loadBattleScript(char *path)
{
	Battle		battle;
	ParserResult	file = Parser_parseFile(path, NULL);
	ParserObj	*buffer;
	ParserObj	*buffer2;

	memset(&battle, 0, sizeof(battle));
	battle.type = BATTLE_ERROR;
	if (file.error) {
		printf("%s: %s\n", ERROR, file.error);
		file.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, file.error);
		dispMsg("Battle Error", file.error, 0);
		free(file.error);
		battle.type = BATTLE_ERROR;
		return battle;
	} else if (file.type != ParserObjType)
		return invalidData(path, "Invalid type found in file");
	if (buffer = ParserObj_getElement(file.data, "type")) {
		if (buffer->type == ParserStringType) {
			if (strcmp(ParserString_toCharStar(buffer->data), "DANMAKU"))
				battle.type = DANMAKU_BATTLE;
			else {
				buffer = (void *)concatf("Unknown battle type '%s'\n", ParserString_toCharStar(buffer->data));
				battle = invalidData(path, (void *)buffer);
				free(buffer);
				return battle;
			}
		} else if (buffer->type == ParserIntType) {
			battle.type = ParserInt_toInt(buffer->data);
		} else
			return invalidData(path, "Invalid type for field \"type\"");
	} else
		return invalidData(path, "Field \"type\" is missing");
	if (buffer = ParserObj_getElement(file.data, "battle_name")) {
		if (buffer->type == ParserStringType) {
			battle.name = strdup(ParserString_toCharStar(buffer->data));
		} else
			return invalidData(path, "Invalid type for field \"battle_name\"");
	} else
		printf("%s: Field \"battle_name\" is missing", WARNING);
	if (buffer = ParserObj_getElement(file.data, "boss_name")) {
		if (buffer->type == ParserStringType) {
			strcpy(battle.boss.name, ParserString_toCharStar(buffer->data));
		} else
			return invalidData(path, "Invalid type for field \"boss_name\"");
	} else
		printf("%s: Field \"boss_name\" is missing", WARNING);
	if (buffer = ParserObj_getElement(file.data, "boss_sprite_sheet")) {
		if (buffer->type == ParserStringType) {
			battle.bossSprite = createSprite((Sprite_config){
				ParserString_toCharStar(buffer->data),
				(sfVector2f){1, 1},
				(sfVector2i){0, 0},
				(sfVector2i){0, 0},
			});
		} else if (buffer->type == ParserIntType) {
			battle.bossSprite = ((Sprite *)game.sprites.content)[ParserInt_toInt(buffer->data) % game.sprites.length];
		} else
			return invalidData(path, "Invalid type for field \"boss_sprite_sheet\"");
	} else
		printf("%s: Field \"boss_sprite_sheet\" is missing", WARNING);
	if (buffer = ParserObj_getElement(file.data, "projectiles")) {
		if (buffer->type == ParserStringType) {
			battle.projectileBank = loadProjectiles(ParserString_toCharStar(buffer->data));
		} else
			return invalidData(path, "Invalid type for field \"projectiles\"");
	} else
		return invalidData(path, "Field \"projectiles\" is missing");/*
	{
		"projectiles": "data/battles/alexandre/battle_normal/bullets.json",
		"base_script": "data/battles/alexandre/battle_normal/actions.lua",
		"music": 13,
		"boss_sprite_size": {
			"x": 16,
			"y": 32,
		},
		"boss_hitbox": {
			"x": 16,
			"y": 32,
		}
		"player_hitbox": {
			"x": 4,
			"y": 4,
		}
	}*/
	ParserObj_destroy(file.data);
	return battle;
}

void	battle(game_t *game)
{

}
