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

Array	invalidDataArray(char *path, char *message)
{
	char	*buffer;

	printf("%s: %s: %s\n", ERROR, path, message);
	buffer = concatf("Error: File '%s' contains invalid battle data:\n%s", path, message);
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
				return invalidDataArray(path, "Invalid type for field \"sprite_sheet\"");
		} else
			printf("%s: Field \"sprite_sheet\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "sprite_size")) {
			if (buffer->type == ParserObjType) {
				if (buffer2 = ParserObj_getElement(buffer, "x")) {
					if (buffer->type == ParserIntType) {
						projBuffer.sprite.rect.width = ParserInt_toInt(buffer2->data);
					} else
						return invalidDataArray(path, "Invalid type for field \"x\" in \"sprite_size\"");
				} else
					printf("%s: Field \"x\" is missing in \"sprite_size\"", WARNING);
				if (buffer2 = ParserObj_getElement(buffer, "y")) {
					if (buffer->type == ParserIntType) {
						projBuffer.sprite.rect.height = ParserInt_toInt(buffer2->data);
					} else
						return invalidDataArray(path, "Invalid type for field \"y\" in \"sprite_size\"");
				} else
					printf("%s: Field \"y\" is missing in \"sprite_size\"", WARNING);
			} else
				return invalidDataArray(path, "Invalid type for field \"sprite_size\"");
		} else
			printf("%s: Field \"sprite_size\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "hitbox_size")) {
			if (buffer->type == ParserObjType) {
				if (buffer2 = ParserObj_getElement(buffer, "x")) {
					if (buffer->type == ParserIntType) {
						projBuffer.sprite.rect.width = ParserInt_toInt(buffer2->data);
					} else
						return invalidDataArray(path, "Invalid type for field \"x\" in \"hitbox_size\"");
				} else
					printf("%s: Field \"x\" is missing in \"hitbox_size\"", WARNING);
				if (buffer2 = ParserObj_getElement(buffer, "y")) {
					if (buffer->type == ParserIntType) {
						projBuffer.sprite.rect.height = ParserInt_toInt(buffer2->data);
					} else
						return invalidDataArray(path, "Invalid type for field \"y\" in \"hitbox_size\"");
				} else
					printf("%s: Field \"y\" is missing in \"hitbox_size\"", WARNING);
			} else
				return invalidDataArray(path, "Invalid type for field \"hitbox_size\"");
		} else
			printf("%s: Field \"hitbox_size\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "base_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.speed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.speed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidDataArray(path, "Invalid type for field \"base_speed\"");
		} else
			printf("%s: Field \"base_speed\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "base_acceleration")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.acceleration = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.acceleration = ParserFloat_toFloat(buffer->data);
			} else
				return invalidDataArray(path, "Invalid type for field \"base_acceleration\"");
		} else
			printf("%s: Field \"base_acceleration\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "rotation_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.rotaSpeed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.rotaSpeed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidDataArray(path, "Invalid type for field \"rotation_speed\"");
		} else
			printf("%s: Field \"rotation_speed\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "base_angle")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.angle = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.angle = ParserFloat_toFloat(buffer->data);
			} else
				return invalidDataArray(path, "Invalid type for field \"base_angle\"");
		} else
			printf("%s: Field \"base_angle\" is missing", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "animation_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.animSpeed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.animSpeed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidDataArray(path, "Invalid type for field \"animation_speed\"");
		} else
			printf("%s: Field \"animation_speed\" is missing", WARNING);
		projBuffer.clock = sfClock_create();
		((Projectile *)array.content)[i] = projBuffer;
	}
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
		return invalidData(path, "Field \"projectiles\" is missing");
	if (buffer = ParserObj_getElement(file.data, "base_script")) {
		if (buffer->type == ParserStringType) {
			battle.script = strdup(ParserString_toCharStar(buffer->data));
		} else
			return invalidData(path, "Invalid type for field \"base_script\"");
	} else
		return invalidData(path, "Field \"base_script\" is missing");
	if (buffer = ParserObj_getElement(file.data, "music")) {
		if (buffer->type == ParserStringType) {
			battle.music = createMusic((Music_config){
				ParserString_toCharStar(buffer->data),
				true,
			});
		} else if (buffer->type == ParserIntType) {
			battle.music = ((sfMusic **)game.musics.content)[ParserInt_toInt(buffer->data) % game.musics.length];
		} else
			return invalidData(path, "Invalid type for field \"music\"");
	} else
		printf("%s: Field \"boss_sprite_sheet\" is missing", WARNING);
	if (buffer = ParserObj_getElement(file.data, "boss_sprite_size")) {
		if (buffer->type == ParserObjType) {
			if (buffer2 = ParserObj_getElement(buffer, "x")) {
				if (buffer->type == ParserIntType) {
					battle.bossSprite.rect.width = ParserInt_toInt(buffer2->data);
				} else
					return invalidData(path, "Invalid type for field \"x\" in \"boss_sprite_size\"");
			} else
				printf("%s: Field \"x\" is missing in \"boss_sprite_size\"", WARNING);
			if (buffer2 = ParserObj_getElement(buffer, "y")) {
				if (buffer->type == ParserIntType) {
					battle.bossSprite.rect.height = ParserInt_toInt(buffer2->data);
				} else
					return invalidData(path, "Invalid type for field \"y\" in \"boss_sprite_size\"");
			} else
				printf("%s: Field \"y\" is missing in \"boss_sprite_size\"", WARNING);
		} else
			return invalidData(path, "Invalid type for field \"boss_sprite_size\"");
	} else
		printf("%s: Field \"boss_sprite_size\" is missing", WARNING);
	if (buffer = ParserObj_getElement(file.data, "boss_hitbox")) {
		if (buffer->type == ParserObjType) {
			if (buffer2 = ParserObj_getElement(buffer, "x")) {
				if (buffer->type == ParserIntType) {
					battle.bossHitbox.x = ParserInt_toInt(buffer2->data);
				} else
					return invalidData(path, "Invalid type for field \"x\" in \"boss_hitbox\"");
			} else
				printf("%s: Field \"x\" is missing in \"boss_hitbox\"", WARNING);
			if (buffer2 = ParserObj_getElement(buffer, "y")) {
				if (buffer->type == ParserIntType) {
					battle.bossHitbox.y = ParserInt_toInt(buffer2->data);
				} else
					return invalidData(path, "Invalid type for field \"y\" in \"boss_hitbox\"");
			} else
				printf("%s: Field \"y\" is missing in \"boss_hitbox\"", WARNING);
		} else
			return invalidData(path, "Invalid type for field \"boss_hitbox\"");
	} else
		printf("%s: Field \"boss_hitbox\" is missing", WARNING);
	if (buffer = ParserObj_getElement(file.data, "player_hitbox")) {
		if (buffer->type == ParserObjType) {
			if (buffer2 = ParserObj_getElement(buffer, "x")) {
				if (buffer->type == ParserIntType) {
					battle.playerHitbox.x = ParserInt_toInt(buffer2->data);
				} else
					return invalidData(path, "Invalid type for field \"x\" in \"player_hitbox\"");
			} else
				printf("%s: Field \"x\" is missing in \"player_hitbox\"", WARNING);
			if (buffer2 = ParserObj_getElement(buffer, "y")) {
				if (buffer->type == ParserIntType) {
					battle.playerHitbox.y = ParserInt_toInt(buffer2->data);
				} else
					return invalidData(path, "Invalid type for field \"y\" in \"player_hitbox\"");
			} else
				printf("%s: Field \"y\" is missing in \"player_hitbox\"", WARNING);
		} else
			return invalidData(path, "Invalid type for field \"player_hitbox\"");
	} else
		printf("%s: Field \"boss_hitbox\" is missing", WARNING);
/*	{
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
