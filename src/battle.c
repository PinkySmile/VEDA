#include "functions.h"
#include "concatf.h"
#include "structs.h"
#include "configParser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern game_t game;

Battle	invalidData(ParserResult result, char *path, char *message)
{
	Battle		battle;
	char		*buffer;

	Parser_destroyData(result.data, result.type);
	memset(&battle, 0, sizeof(battle));
	battle.type = BATTLE_ERROR;
	printf("%s: %s: %s\n", ERROR, path, message);
	buffer = concatf("Error: File '%s' contains invalid battle data:\n%s", path, message);
	dispMsg("Battle Error", buffer, 0);
	free(buffer);
	return battle;
}

Array	invalidDataArray(ParserResult result, char *path, char *message)
{
	char	*buffer;

	Parser_destroyData(result.data, result.type);
	printf("%s: %s: %s\n", ERROR, path, message);
	buffer = concatf("Error: File '%s' contains invalid battle data:\n%s", path, message);
	dispMsg("Battle Error", buffer, 0);
	free(buffer);
	return (Array){NULL, -1};
}

Battle	invalidType(ParserResult result, char *path, char *message, ParserTypes got, ParserTypes expected)
{
	Battle		battle;
	char		*buffer;

	Parser_destroyData(result.data, result.type);
	memset(&battle, 0, sizeof(battle));
	battle.type = BATTLE_ERROR;
	printf("%s: %s: %s\n", ERROR, path, message);
	buffer = concatf("Error: File '%s' contains invalid battle data:\n%s:\n%s expected but got %s\n", path, message, typeToString(expected), typeToString(got));
	dispMsg("Battle Error", buffer, 0);
	free(buffer);
	return battle;
}

Array	invalidTypeArray(ParserResult result, char *path, char *message, ParserTypes got, ParserTypes expected)
{
	char	*buffer;

	Parser_destroyData(result.data, result.type);
	printf("%s: %s: %s\n", ERROR, path, message);
	buffer = concatf("Error: File '%s' contains invalid battle data:\n%s:\n%s expected but got %s\n", path, message, typeToString(expected), typeToString(got));
	dispMsg("Battle Error", buffer, 0);
	free(buffer);
	return (Array){NULL, -1};
}

Array	loadProjectiles(char *path)
{
	ParserResult	result = Parser_parseFile(path, JSON_TO_ARRAY);
	ParserObj	*buffer;
	ParserObj	*buffer2;
	ParserObj	*currProjectile;
	Projectile	projBuffer;
	Array		array;

	printf("%s: Loading projectiles in file %s\n", INFO, path);
	if (result.error) {
		printf("%s: %s\n", ERROR, result.error);
		result.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, result.error);
		dispMsg("Battle Error", result.error, 0);
		free(result.error);
		return (Array){NULL, -1};
	} else if (result.type != ParserArrayType) {
		printf("%s: %s: Invalid type\n", ERROR, path);
		buffer = (void *)concatf("Error: %s: Invalid type found in the file\n", path);
		dispMsg("Battle Error", (void *)buffer, 0);
		free(buffer);
		return (Array){NULL, -1};
	} else if (((ParserArray *)result.data)->type != ParserObjType) {
		printf("%s: %s: Invalid type\n", ERROR, path);
		buffer = (void *)concatf("Error: %s: Array contains invalid data\n", path);
		dispMsg("Battle Error", (void *)buffer, 0);
		free(buffer);
		return (Array){NULL, -1};
	}
	array.length = ((ParserArray *)result.data)->length;
	array.content = malloc(array.length * sizeof(Projectile));
	memset(array.content, 0, array.length * sizeof(Projectile));
	for (int i = 0; i < array.length; i++) {
		currProjectile = ParserArray_getElement(result.data, i);
		if (buffer = ParserObj_getElement(currProjectile, "sprite_sheet")) {
			if (buffer->type == ParserStringType) {
				projBuffer.sprite = createSprite((Sprite_config)
				{
					ParserString_toCharStar(buffer->data),
				        (sfVector2f){1, 1},
					(sfVector2i){0, 0},
					(sfVector2i){0, 0},
				});
				projBuffer.needToDestroySprite = true;
			} else if (buffer->type == ParserIntType) {
				projBuffer.sprite = ((Sprite *)game.sprites.content)[ParserInt_toInt(buffer->data) % game.sprites.length];
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"sprite_sheet\"", buffer->type, ParserStringType);
		} else
			printf("%s: Field \"sprite_sheet\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "sprite_size")) {
			if (buffer->type == ParserObjType) {
				if (buffer2 = ParserObj_getElement(buffer->data, "x")) {
					if (buffer2->type == ParserIntType) {
						projBuffer.sprite.rect.width = ParserInt_toInt(buffer2->data);
					} else
						return invalidTypeArray(result, path, "Invalid type for field \"x\" in \"sprite_size\"", buffer2->type, ParserIntType);
				} else
					printf("%s: Field \"x\" is missing in \"sprite_size\"\n", WARNING);
				if (buffer2 = ParserObj_getElement(buffer->data, "y")) {
					if (buffer2->type == ParserIntType) {
						projBuffer.sprite.rect.height = ParserInt_toInt(buffer2->data);
					} else
						return invalidTypeArray(result, path, "Invalid type for field \"y\" in \"sprite_size\"", buffer2->type, ParserIntType);
				} else
					printf("%s: Field \"y\" is missing in \"sprite_size\"\n", WARNING);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"sprite_size\"", buffer->type, ParserObjType);
		} else
			printf("%s: Field \"sprite_size\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "hitbox_size")) {
			if (buffer->type == ParserObjType) {
				if (buffer2 = ParserObj_getElement(buffer->data, "x")) {
					if (buffer2->type == ParserIntType) {
						projBuffer.hitbox.x = ParserInt_toInt(buffer2->data);
					} else
						return invalidTypeArray(result, path, "Invalid type for field \"x\" in \"hitbox_size\"", buffer2->type, ParserIntType);
				} else
					printf("%s: Field \"x\" is missing in \"hitbox_size\"\n", WARNING);
				if (buffer2 = ParserObj_getElement(buffer->data, "y")) {
					if (buffer2->type == ParserIntType) {
						projBuffer.hitbox.y = ParserInt_toInt(buffer2->data);
					} else
						return invalidTypeArray(result, path, "Invalid type for field \"y\" in \"hitbox_size\"", buffer2->type, ParserIntType);
				} else
					printf("%s: Field \"y\" is missing in \"hitbox_size\"\n", WARNING);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"hitbox_size\"", buffer->type, ParserObjType);
		} else
			printf("%s: Field \"hitbox_size\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "base_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.speed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.speed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"base_speed\"", buffer->type, ParserFloatType);
		} else
			printf("%s: Field \"base_speed\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "base_acceleration")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.acceleration = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.acceleration = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"base_acceleration\"", buffer->type, ParserFloatType);
		} else
			printf("%s: Field \"base_acceleration\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "rotation_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.rotaSpeed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.rotaSpeed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"rotation_speed\"", buffer->type, ParserFloatType);
		} else
			printf("%s: Field \"rotation_speed\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "base_angle")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.angle = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.angle = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"base_angle\"", buffer->type, ParserFloatType);
		} else
			printf("%s: Field \"base_angle\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "animation_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.animSpeed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.animSpeed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"animation_speed\"", buffer->type, ParserFloatType);
		} else
			printf("%s: Field \"animation_speed\" is missing\n", WARNING);
		projBuffer.clock = sfClock_create();
		((Projectile *)array.content)[i] = projBuffer;
	}
	Parser_destroyData(result.data, result.type);
	return array;
}

Battle	loadBattleScript(char *path)
{
	Battle		battle;
	ParserResult	result = Parser_parseFile(path, NULL);
	ParserObj	*buffer;
	ParserObj	*buffer2;

	printf("%s: Loading %s as battle infos\n", INFO, path);
	memset(&battle, 0, sizeof(battle));
	battle.type = BATTLE_ERROR;
	if (result.error) {
		printf("%s: %s\n", ERROR, result.error);
		result.error = concatf("Error: Couldn't load file '%s':\n%s\n", path, result.error);
		dispMsg("Battle Error", result.error, 0);
		free(result.error);
		battle.type = BATTLE_ERROR;
		return battle;
	} else if (result.type != ParserObjType)
		return invalidType(result, path, "Invalid type found in file", result.type, ParserObjType);
	if (buffer = ParserObj_getElement(result.data, "type")) {
		if (buffer->type == ParserStringType) {
			if (strcmp(ParserString_toCharStar(buffer->data), "DANMAKU") == 0)
				battle.type = DANMAKU_BATTLE;
			else {
				buffer = (void *)concatf("Unknown battle type '%s'", ParserString_toCharStar(buffer->data));
				battle = invalidData(result, path, (void *)buffer);
				free(buffer);
				return battle;
			}
		} else if (buffer->type == ParserIntType) {
			battle.type = ParserInt_toInt(buffer->data);
		} else
			return invalidType(result, path, "Invalid type for field \"type\"", buffer->type, ParserStringType);
	} else
		return invalidData(result, path, "Field \"type\" is missing");
	if (buffer = ParserObj_getElement(result.data, "battle_name")) {
		if (buffer->type == ParserStringType) {
			battle.name = strdup(ParserString_toCharStar(buffer->data));
		} else
			return invalidType(result, path, "Invalid type for field \"battle_name\"", buffer->type, ParserStringType);
	} else
		printf("%s: Field \"battle_name\" is missing", WARNING);
	if (buffer = ParserObj_getElement(result.data, "boss_name")) {
		if (buffer->type == ParserStringType) {
			strcpy(battle.boss.name, ParserString_toCharStar(buffer->data));
		} else
			return invalidType(result, path, "Invalid type for field \"boss_name\"", buffer->type, ParserStringType);
	} else
		printf("%s: Field \"boss_name\" is missing\n", WARNING);
	if (buffer = ParserObj_getElement(result.data, "boss_sprite_sheet")) {
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
			return invalidType(result, path, "Invalid type for field \"boss_sprite_sheet\"", buffer->type, ParserStringType);
	} else
		printf("%s: Field \"boss_sprite_sheet\" is missing\n", WARNING);
	if (buffer = ParserObj_getElement(result.data, "projectiles")) {
		if (buffer->type == ParserStringType) {
			battle.projectileBank = loadProjectiles(ParserString_toCharStar(buffer->data));
		} else
			return invalidType(result, path, "Invalid type for field \"projectiles\"", buffer->type, ParserStringType);
	} else
		return invalidData(result, path, "Field \"projectiles\" is missing");
	if (buffer = ParserObj_getElement(result.data, "base_script")) {
		if (buffer->type == ParserStringType) {
			battle.script = strdup(ParserString_toCharStar(buffer->data));
		} else
			return invalidType(result, path, "Invalid type for field \"base_script\"", buffer->type, ParserStringType);
	} else
		return invalidData(result, path, "Field \"base_script\" is missing");
	if (buffer = ParserObj_getElement(result.data, "music")) {
		if (buffer->type == ParserStringType) {
			battle.music = createMusic((Music_config){
				ParserString_toCharStar(buffer->data),
				true,
			});
		} else if (buffer->type == ParserIntType) {
			battle.music = ((sfMusic **)game.musics.content)[ParserInt_toInt(buffer->data) % game.musics.length];
		} else
			return invalidType(result, path, "Invalid type for field \"music\"", buffer->type, ParserStringType);
	} else
		printf("%s: Field \"boss_sprite_sheet\" is missing\n", WARNING);
	if (buffer = ParserObj_getElement(result.data, "boss_sprite_size")) {
		if (buffer->type == ParserObjType) {
			if (buffer2 = ParserObj_getElement(buffer->data, "x")) {
				if (buffer2->type == ParserIntType) {
					battle.bossSprite.rect.width = ParserInt_toInt(buffer2->data);
				} else
					return invalidType(result, path, "Invalid type for field \"x\" in \"boss_sprite_size\"", buffer2->type, ParserIntType);
			} else
				printf("%s: Field \"x\" is missing in \"boss_sprite_size\"\n", WARNING);
			if (buffer2 = ParserObj_getElement(buffer->data, "y")) {
				if (buffer2->type == ParserIntType) {
					battle.bossSprite.rect.height = ParserInt_toInt(buffer2->data);
				} else
					return invalidType(result, path, "Invalid type for field \"y\" in \"boss_sprite_size\"", buffer2->type, ParserIntType);
			} else
				printf("%s: Field \"y\" is missing in \"boss_sprite_size\"\n", WARNING);
		} else
			return invalidType(result, path, "Invalid type for field \"boss_sprite_size\"", buffer->type, ParserObjType);
	} else
		printf("%s: Field \"boss_sprite_size\" is missing\n", WARNING);
	if (buffer = ParserObj_getElement(result.data, "boss_hitbox")) {
		if (buffer->type == ParserObjType) {
			if (buffer2 = ParserObj_getElement(buffer->data, "x")) {
				if (buffer2->type == ParserIntType) {
					battle.bossHitbox.x = ParserInt_toInt(buffer2->data);
				} else
					return invalidType(result, path, "Invalid type for field \"x\" in \"boss_hitbox\"", buffer2->type, ParserIntType);
			} else
				printf("%s: Field \"x\" is missing in \"boss_hitbox\"\n", WARNING);
			if (buffer2 = ParserObj_getElement(buffer->data, "y")) {
				if (buffer2->type == ParserIntType) {
					battle.bossHitbox.y = ParserInt_toInt(buffer2->data);
				} else
					return invalidType(result, path, "Invalid type for field \"y\" in \"boss_hitbox\"", buffer2->type, ParserIntType);
			} else
				printf("%s: Field \"y\" is missing in \"boss_hitbox\"\n", WARNING);
		} else
			return invalidType(result, path, "Invalid type for field \"boss_hitbox\"", buffer->type, ParserIntType);
	} else
		printf("%s: Field \"boss_hitbox\" is missing\n", WARNING);
	if (buffer = ParserObj_getElement(result.data, "player_hitbox")) {
		if (buffer->type == ParserObjType) {
			if (buffer2 = ParserObj_getElement(buffer->data, "x")) {
				if (buffer2->type == ParserIntType) {
					battle.playerHitbox.x = ParserInt_toInt(buffer2->data);
				} else
					return invalidType(result, path, "Invalid type for field \"x\" in \"player_hitbox\"", buffer2->type, ParserIntType);
			} else
				printf("%s: Field \"x\" is missing in \"player_hitbox\"\n", WARNING);
			if (buffer2 = ParserObj_getElement(buffer->data, "y")) {
				if (buffer2->type == ParserIntType) {
					battle.playerHitbox.y = ParserInt_toInt(buffer2->data);
				} else
					return invalidType(result, path, "Invalid type for field \"y\" in \"player_hitbox\"", buffer2->type, ParserIntType);
			} else
				printf("%s: Field \"y\" is missing in \"player_hitbox\"\n", WARNING);
		} else
			return invalidType(result, path, "Invalid type for field \"player_hitbox\"", buffer->type, ParserObjType);
	} else
		printf("%s: Field \"boss_hitbox\" is missing\n", WARNING);
	ParserObj_destroy(result.data);
	return battle;
}

void	battle(game_t *game)
{
	displayLowerLayer(game);
	displayCharacters(game);
	displayCharacter(&game->battle_infos.boss, game, 10, game->battle_infos.bossSprite.sprite);
	displayUpperLayer(game);
	displayHUD(game);
	movePlayer(game);
}
