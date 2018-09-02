#include "functions.h"
#include "concatf.h"
#include "structs.h"
#include "configParser.h"
#include "battle_api.h"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	proj2string(lua_State *Lua)
{
	Projectile	**proj = luaL_checkudata(Lua, 1, "projectile");

	luaL_argcheck(Lua, proj != NULL, 1, "'projectile' expected");
	lua_pushfstring(Lua, "projectile: %p", *proj);
	return 1;
}

int	char2string(lua_State *Lua)
{
	Character	**proj = luaL_checkudata(Lua, 1, "character");

	luaL_argcheck(Lua, proj != NULL, 1, "'character' expected");
	lua_pushfstring(Lua, "character ('%s')", (*proj)->name);
	return 1;
}

const luaL_Reg game_api[] = {
	{"playSound", playSoundLua},
	{"yield", yield},
	{"stopTime", stopTime},
	{"addProjectile", addProjectileLua},
	{"getElapsedTime", getElapsedTime},
	{NULL, NULL}
};

const luaL_Reg character_lib[] = {
	{"__index", getCharacterField},
	{"__newindex", setCharacterField},
	{"__tostring", char2string},
	{NULL, NULL}
};

const luaL_Reg projectiles_lib[] = {
	{"setToRemove", destroyProjectile},
	{"__index", getProjectileField},
	{"__newindex", setProjectileField},
	{"__tostring", proj2string},
	{NULL, NULL}
};

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
	sfVector2f	scaling = game.settings.baseScale;
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
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};
	} else if (((ParserArray *)result.data)->type != ParserObjType) {
		printf("%s: %s: Invalid type\n", ERROR, path);
		buffer = (void *)concatf("Error: %s: Array contains invalid data\n", path);
		dispMsg("Battle Error", (void *)buffer, 0);
		free(buffer);
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};
	}
	array.length = ((ParserArray *)result.data)->length;
	array.content = malloc(array.length * sizeof(Projectile));
	memset(array.content, 0, array.length * sizeof(Projectile));
	for (int i = 0; i < array.length; i++) {
		scaling = (sfVector2f){1, 1};
		currProjectile = ParserArray_getElement(result.data, i);
		memset(&projBuffer, 0, sizeof(projBuffer));
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
				projBuffer.sprite = ((Sprite *)game.ressources.sprites.content)[ParserInt_toInt(buffer->data) % game.ressources.sprites.length];
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"sprite_sheet\"", buffer->type, ParserStringType);
		} else
			printf("%s: Field \"sprite_sheet\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "sprite_size")) {
			if (buffer->type == ParserObjType) {
				projBuffer.sprite.rect.width = projBuffer.sprite.texture ? sfTexture_getSize(projBuffer.sprite.texture).x : 0;
				projBuffer.sprite.rect.height = projBuffer.sprite.texture ? sfTexture_getSize(projBuffer.sprite.texture).y : 0;
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
		if (buffer = ParserObj_getElement(currProjectile, "bullet_size")) {
			if (buffer->type == ParserObjType) {
				if (buffer2 = ParserObj_getElement(buffer->data, "x")) {
					if (buffer2->type == ParserIntType) {
						scaling.x = game.settings.baseScale.x * (float)ParserInt_toInt(buffer2->data) / (float)projBuffer.sprite.rect.width;
					} else
						return invalidTypeArray(result, path, "Invalid type for field \"x\" in \"bullet_size\"", buffer2->type, ParserIntType);
				} else
					printf("%s: Field \"x\" is missing in \"bullet_size\"\n", WARNING);
				if (buffer2 = ParserObj_getElement(buffer->data, "y")) {
					if (buffer2->type == ParserIntType) {
						scaling.y = game.settings.baseScale.y * (float)ParserInt_toInt(buffer2->data) / (float)projBuffer.sprite.rect.height;
					} else
						return invalidTypeArray(result, path, "Invalid type for field \"y\" in \"bullet_size\"", buffer2->type, ParserIntType);
				} else
					printf("%s: Field \"y\" is missing in \"bullet_size\"\n", WARNING);
				if (projBuffer.sprite.sprite)
					sfSprite_setScale(projBuffer.sprite.sprite, scaling);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"bullet_size\"", buffer->type, ParserObjType);
		} else
			printf("%s: Field \"hitbox_size\" is missing\n", WARNING);
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
		} else {
			projBuffer.minSpeed = -1000;
			printf("%s: Field \"base_speed\" is missing\n", WARNING);
		}
		if (buffer = ParserObj_getElement(currProjectile, "min_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.minSpeed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.minSpeed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"min_speed\"", buffer->type, ParserFloatType);
		} else
			printf("%s: Field \"min_speed\" is missing\n", WARNING);
		if (buffer = ParserObj_getElement(currProjectile, "max_speed")) {
		        if (buffer->type == ParserIntType) {
				projBuffer.maxSpeed = ParserInt_toInt(buffer->data);
			} else if (buffer->type == ParserFloatType) {
				projBuffer.maxSpeed = ParserFloat_toFloat(buffer->data);
			} else
				return invalidTypeArray(result, path, "Invalid type for field \"max_speed\"", buffer->type, ParserFloatType);
		} else {
			projBuffer.maxSpeed = 1000;
			printf("%s: Field \"max_speed\" is missing\n", WARNING);
		}
		if (projBuffer.maxSpeed < projBuffer.minSpeed) {
			return invalidTypeArray(result, path, "Maximum speed is lower than minimum speed", buffer->type, ParserFloatType);
		}
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
		projBuffer.bankID = i;
		if (projBuffer.sprite.sprite)
			sfSprite_setOrigin(projBuffer.sprite.sprite, (sfVector2f){(float)projBuffer.sprite.rect.width / 2, (float)projBuffer.sprite.rect.height / 2});
		((Projectile *)array.content)[i] = projBuffer;
	}
	Parser_destroyData(result.data, result.type);
	return array;
}

void	addDependencies(lua_State *Lua)
{
	luaL_openlibs(Lua);

	luaL_newmetatable(Lua, "projectile");
	lua_pushstring(Lua, "__index");
	lua_pushvalue(Lua, -2);
	lua_settable(Lua, -3);
	luaL_openlib(Lua, NULL, projectiles_lib, 0);

	luaL_newmetatable(Lua, "character");
	lua_pushstring(Lua, "__index");
	lua_pushvalue(Lua, -2);
	lua_settable(Lua, -3);
	luaL_openlib(Lua, NULL, character_lib, 0);

	//luaL_newmetatable(Lua, "sound_object");
	luaL_openlib(Lua, "vedaApi", game_api, 0);
	/*lua_pushcfunction(Lua, &getElapsedTime);
	lua_setglobal(Lua, "getElapsedTime");
	lua_pushcfunction(Lua, &addProjectileLua);
	lua_setglobal(Lua, "addProjectile");
	lua_pushcfunction(Lua, &stopTime);
	lua_setglobal(Lua, "stopTime");
	lua_pushcfunction(Lua, &yield);
	lua_setglobal(Lua, "yield");
	lua_pushcfunction(Lua, &playSoundLua);
	lua_setglobal(Lua, "playSound"); */
}

Battle	loadBattleScript(char *path)
{
	Battle		battle = game.state.battle_infos;
	int		err;
	ParserResult	result = Parser_parseFile(path, NULL);
	ParserObj	*buffer;
	ParserObj	*buffer2;

	printf("%s: Loading %s as battle infos\n", INFO, path);
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
				ParserObj_destroy(result.data);
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
			battle.needToDestroySprite = true;
		} else if (buffer->type == ParserIntType) {
			battle.bossSprite = ((Sprite *)game.ressources.sprites.content)[ParserInt_toInt(buffer->data) % game.ressources.sprites.length];
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
			battle.Lua  = luaL_newstate();
			battle.script = strdup(ParserString_toCharStar(buffer->data));
			addDependencies(battle.Lua);
			err = luaL_dofile(battle.Lua, ParserString_toCharStar(buffer->data));
			if (err) {
				buffer = (void *)concatf("An unexpected error occurred when loading %s", ParserString_toCharStar(buffer->data));
				battle = invalidData(result, path, (void *)buffer);
				free(buffer);
				return battle;
			}
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
			battle.music = ((sfMusic **)game.ressources.musics.content)[ParserInt_toInt(buffer->data) % game.ressources.musics.length];
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
	for (int j = 0; j < DAMAGES_TYPE_NB; j++)
	        battle.boss.damageClock[j] = sfClock_create();
	battle.clock = sfClock_create();
	return battle;
}

void	updateProjectiles(list_t *proj_list)
{
	Projectile	*proj;
	list_t		*buffer;

	for (list_t *list = proj_list; list && list->data; list = list->next) {
		proj = list->data;
		while (proj->toRemove) {
			buffer = list->next;
			sfClock_destroy(proj->clock);
			sfClock_destroy(proj->animClock);
			free(proj);
			if (list->prev) {
				list->prev->next = list->next;
			} else {
				if (!list->next) {
					list->data = NULL;
					return;
				} else {
					list->data = list->next->data;
					list->next = list->next->next;
					free(buffer);
					buffer = list->next;
				}
			}
			if (list->next) {
				list->next->prev = list->prev;
			} else
				return;
			list = buffer;
			proj = list->data;
			if (!proj)
				break;
		}
	}
	for (list_t *list = proj_list; list && list->data; list = list->next) {
		proj = list->data;
		proj->pos.x += cos(proj->angle * M_PI / 180) * proj->speed;
		proj->pos.y += sin(proj->angle * M_PI / 180) * proj->speed;
		proj->speed += proj->acceleration;
		if (proj->speed > proj->maxSpeed)
			proj->speed = proj->maxSpeed;
		if (proj->speed < proj->minSpeed)
			proj->speed = proj->minSpeed;
		proj->angle += proj->rotaSpeed;
	}
}

void	displayProjectiles()
{
	Projectile	*proj;
	sfVector2f	pos;

	for (list_t *list = &game.state.battle_infos.projectiles; list && list->data; list = list->next) {
		proj = list->data;
		if (proj->animSpeed >= 0 && sfTime_asSeconds(sfClock_getElapsedTime(proj->animClock)) >= proj->animSpeed) {
			sfClock_restart(proj->animClock);
			proj->animation = (proj->animation >= ((int)sfTexture_getSize(proj->sprite.texture).x / proj->sprite.rect.width) - 1) ? 0 : proj->animation + 1;
		}
		proj->sprite.rect.left = proj->animation * proj->sprite.rect.width;
		pos.x = (proj->pos.x + game.state.cameraPos.x) * game.settings.baseScale.x;
		pos.y = (proj->pos.y + game.state.cameraPos.y) * game.settings.baseScale.y;
		while (proj->angle > 360)
			proj->angle -= 360;
		while (proj->angle < 360)
			proj->angle += 360;
		sfSprite_setRotation(proj->sprite.sprite, proj->angle);
		sfSprite_setPosition(proj->sprite.sprite, pos);
		sfSprite_setTextureRect(proj->sprite.sprite, proj->sprite.rect);
		sfRenderWindow_drawSprite(game.ressources.window, proj->sprite.sprite, NULL);
	}
}

sfIntRect	getRect(sfVector2u size, sfVector2u imgSize, int anim)
{
	sfIntRect	rect;

	rect.top = size.x * (anim / ((imgSize.x - imgSize.x % size.x) / size.x));
	rect.left = size.x * anim % (imgSize.x - imgSize.x % size.x);
	rect.width = size.x;
	rect.height = size.y;
	return (rect);
}

void	battle()
{
	static	bool		launchLua = true;
	static	lua_State	*Lua = NULL;
	int			err;
	char			*buffer;

	game.state.battle_infos.player = getPlayer(game.state.characters.content, game.state.characters.length);
	if (launchLua) {
		if (!game.state.battle_infos.Lua) {
			game.state.menu = 1;
			return;
		}
		game.state.battle_infos.Lua_thread = lua_newthread(game.state.battle_infos.Lua);
		launchLua = false;
		pushCharacter(game.state.battle_infos.Lua_thread, game.state.battle_infos.player);
		lua_setglobal(game.state.battle_infos.Lua_thread, "player");
		pushCharacter(game.state.battle_infos.Lua_thread, &game.state.battle_infos.boss);
		lua_setglobal(game.state.battle_infos.Lua_thread, "boss");
		lua_getglobal(game.state.battle_infos.Lua_thread, "bossAI");
	}
	if (game.state.battle_infos.yieldTime <= 0) {
		err = lua_resume(game.state.battle_infos.Lua_thread, game.state.battle_infos.Lua, 0);
		if (err == LUA_ERRRUN) {
			buffer = concatf("A runtime error occurred during battle:\n%s", luaL_checkstring(game.state.battle_infos.Lua_thread, -1));
			printf("%s: %s\n", ERROR, lua_tostring(Lua, -1));
			dispMsg("Battle Error", buffer, 0);
			free(buffer);
			back_on_title_screen(-1);
			if (game.state.battle_infos.music)
				sfMusic_stop(game.state.battle_infos.music);
			launchLua = true;
			return;
		} else if (err == LUA_ERRMEM) {
			buffer = concatf("A runtime error occurred during battle:\n%s: Out of memory", game.state.battle_infos.script);
			printf("%s: %s: Out of memory\n", ERROR, game.state.battle_infos.script);
			dispMsg("Battle Error", buffer, 0);
			free(buffer);
			back_on_title_screen(-1);
			if (game.state.battle_infos.music)
				sfMusic_stop(game.state.battle_infos.music);
			launchLua = true;
			return;
		} else if (err == LUA_ERRERR) {
			buffer = concatf("An unexpected error occurred during battle:\n%s", game.state.battle_infos.script);
			printf("%s: %s: Unknown error\n", ERROR, game.state.battle_infos.script);
			dispMsg("Battle Error", buffer, 0);
			free(buffer);
			back_on_title_screen(-1);
			sfMusic_stop(game.state.battle_infos.music);
			launchLua = true;
			return;
		} else if (!err) {
			launchLua = true;
			game.state.menu = 1;
			if (game.state.battle_infos.music)
				sfMusic_stop(game.state.battle_infos.music);
			return;
		}
	}
	if (game.state.battle_infos.music && sfMusic_getStatus(game.state.battle_infos.music) != sfPlaying) {
		for (int i = 0; i < game.ressources.musics.length; i++)
			if (((sfMusic **)game.ressources.musics.content)[i] && sfMusic_getStatus(game.state.battle_infos.music) == sfPlaying)
				sfMusic_stop(((sfMusic **)game.ressources.musics.content)[i]);
		sfMusic_play(game.state.battle_infos.music);
		sfMusic_setVolume(game.state.battle_infos.music, game.settings.musicVolume);
	}
	if (game.state.battle_infos.yieldTime > 0)
		game.state.battle_infos.yieldTime--;
	displayLowerLayer();
	displayCharacters();
	if (game.state.battle_infos.bossSprite.sprite) {
		game.state.battle_infos.bossSprite.rect = getRect(
			(sfVector2u){game.state.battle_infos.bossSprite.rect.width, game.state.battle_infos.bossSprite.rect.height},
			sfTexture_getSize(game.state.battle_infos.bossSprite.texture),
			game.state.battle_infos.boss.movement.animation
		);
		sfSprite_setTextureRect(game.state.battle_infos.bossSprite.sprite, game.state.battle_infos.bossSprite.rect);
		image(game.state.battle_infos.bossSprite.sprite, game.state.battle_infos.boss.movement.pos.x + game.state.cameraPos.x, game.state.battle_infos.boss.movement.pos.y + game.state.cameraPos.y, -1, -1);
	} else {
		sfRectangleShape_setOutlineColor(game.ressources.rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){255, 0, 0, 255});
		rect(game.state.battle_infos.boss.movement.pos.x + game.state.cameraPos.x, game.state.battle_infos.boss.movement.pos.y + game.state.cameraPos.y, game.state.battle_infos.bossSprite.rect.width, game.state.battle_infos.bossSprite.rect.height);
	}
	displayUpperLayer();
	displayProjectiles();
	displayHUD();
	if (!game.state.battle_infos.timeStopped) {
		movePlayer();
		updateProjectiles(&game.state.battle_infos.projectiles);
		for (int i = 0; i < game.state.characters.length; i++)
			((Character *)game.state.characters.content)[i].invulnerabiltyTime -= ((Character *)game.state.characters.content)[i].invulnerabiltyTime > 0 ? 1 : 0;
	} else {
		sfRectangleShape_setFillColor(game.ressources.rectangle, (sfColor){255, 230, 255, 55});
		rect(0, 0, 640, 480);
	}
	for (int i = 0; i < game.state.characters.length; i++)
		if (((Character *)game.state.characters.content)[i].stats.life > 10 * ((Character *)game.state.characters.content)[i].stats.lifeMax)
			((Character *)game.state.characters.content)[i].stats.life = 10 * ((Character *)game.state.characters.content)[i].stats.lifeMax;
}
