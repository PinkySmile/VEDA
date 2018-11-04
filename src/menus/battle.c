#include <malloc.h>
#include <math.h>
#include "utils.h"
#include "structs.h"
#include "display.h"
#include "concatf.h"
#include "graphic.h"
#include "callbacks.h"
#include "functions.h"
#include "battle_lua.h"

sfIntRect	getRect(sfVector2u size, sfVector2u imgSize, int anim)
{
	sfIntRect	rect;

	rect.top = size.x * (anim / ((imgSize.x - imgSize.x % size.x) / size.x));
	rect.left = size.x * anim % (imgSize.x - imgSize.x % size.x);
	rect.width = size.x;
	rect.height = size.y;
	return (rect);
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
		sfRenderWindow_drawSprite(game.resources.window, proj->sprite.sprite, NULL);
	}
}

void	updateProjectiles(list_t *proj_list)
{
	Projectile	*proj;
	list_t		*buffer;

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

bool	resumeLuaSession(lua_State *thread, lua_State *Lua)
{
	int	err;
	char	*buffer;

	err = lua_resume(thread, Lua, 0);

	if (err == LUA_ERRRUN) {
		buffer = concatf("A runtime error occurred during battle:\n%s", luaL_checkstring(game.state.battle_infos.lua_thread, -1));
		printf("%s: %s\n", ERROR_BEG, lua_tostring(game.state.battle_infos.lua_thread, -1));
	} else if (err == LUA_ERRMEM) {
		buffer = concatf("A runtime error occurred during battle:\n%s: Out of memory", game.state.battle_infos.script);
		printf("%s: %s: Out of memory\n", ERROR_BEG, game.state.battle_infos.script);
	} else if (err == LUA_ERRERR) {
		buffer = concatf("An unexpected error occurred during battle:\n%s", game.state.battle_infos.script);
		printf("%s: %s: Unknown error\n", ERROR_BEG, game.state.battle_infos.script);
	} else if (!err) {
		game.state.menu = 1;
		if (game.state.battle_infos.music)
			sfMusic_stop(game.state.battle_infos.music);
		return true;
	} else
		return false;

	dispMsg("Battle Error", buffer, 0);
	free(buffer);
	backOnTitleScreen(-1);
	if (game.state.battle_infos.music)
		sfMusic_stop(game.state.battle_infos.music);
	return true;
}

void	initBattle()
{
	if (!game.state.battle_infos.lua) {
		game.state.menu = 1;
		return;
	}
	if (game.state.battle_infos.lua_thread)
		lua_close(game.state.battle_infos.lua_thread);
	game.state.battle_infos.lua_thread = lua_newthread(game.state.battle_infos.lua);
	pushCharacter(game.state.battle_infos.lua_thread, getPlayer());
	lua_setglobal(game.state.battle_infos.lua_thread, "player");
	pushCharacter(game.state.battle_infos.lua_thread, &game.state.battle_infos.boss);
	lua_setglobal(game.state.battle_infos.lua_thread, "boss");
	lua_getglobal(game.state.battle_infos.lua_thread, "bossAI");
}

void	displayBattleBoss()
{
	if (game.state.battle_infos.bossSprite.sprite) {
		game.state.battle_infos.bossSprite.rect = getRect(
			(sfVector2u){
				game.state.battle_infos.bossSprite.rect.width,
				game.state.battle_infos.bossSprite.rect.height
			},
			sfTexture_getSize(game.state.battle_infos.bossSprite.texture),
			game.state.battle_infos.boss.movement.animation
		);
		sfSprite_setTextureRect(
			game.state.battle_infos.bossSprite.sprite,
			game.state.battle_infos.bossSprite.rect
		);
		image(
			game.state.battle_infos.bossSprite.sprite,
			game.state.battle_infos.boss.movement.pos.x + game.state.cameraPos.x,
			game.state.battle_infos.boss.movement.pos.y + game.state.cameraPos.y,
			-1,
			-1
		);

	} else {
		sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){255, 0, 0, 255});
		rect(
			game.state.battle_infos.boss.movement.pos.x + game.state.cameraPos.x,
			game.state.battle_infos.boss.movement.pos.y + game.state.cameraPos.y,
			game.state.battle_infos.bossSprite.rect.width,
			game.state.battle_infos.bossSprite.rect.height
		);
	}

	if (game.debug)
		debug_displayCharacterHitboxs(&game.state.battle_infos.boss);
}

void	battle()
{
	static	bool	launchlua = true;

	if (launchlua) {
		initBattle();
		launchlua = false;
		for (int i = 0; i < game.resources.musics.length; i++)
			if (getMusic(i) && sfMusic_getStatus(game.state.battle_infos.music) == sfPlaying)
				sfMusic_stop(getMusic(i));
		sfMusic_play(game.state.battle_infos.music);
		sfMusic_setVolume(game.state.battle_infos.music, game.settings.musicVolume);
	}

	if (game.state.battle_infos.yieldTime <= 0)
		launchlua = resumeLuaSession(game.state.battle_infos.lua_thread, game.state.battle_infos.lua);

	if (game.state.battle_infos.yieldTime > 0)
		game.state.battle_infos.yieldTime--;

	displayLowerLayer();
	displayCharacters();
	displayBattleBoss();
	displayUpperLayer();
	displayProjectiles();
	displayHUD();

	if (!game.state.battle_infos.timeStopped) {
		moveCharacter(getPlayer(), (sfVector2f){
			isKeyPressed(getKey(KEY_RIGHT), game.resources.window) - isKeyPressed(getKey(KEY_LEFT), game.resources.window),
			isKeyPressed(getKey(KEY_DOWN), game.resources.window) - isKeyPressed(getKey(KEY_UP), game.resources.window),
		});
		updateProjectiles(&game.state.battle_infos.projectiles);
		for (int i = 0; i < game.state.characters.length; i++)
			getCharacter(i)->invulnerabiltyTime -= getCharacter(i)->invulnerabiltyTime > 0 ? 1 : 0;
	} else {
		sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){255, 230, 255, 55});
		rect(0, 0, 640, 480);
	}

	for (int i = 0; i < game.state.characters.length; i++)
		if (getCharacter(i)->stats.life > 10 * getCharacter(i)->stats.lifeMax)
			getCharacter(i)->stats.life = 10 * getCharacter(i)->stats.lifeMax;
}
