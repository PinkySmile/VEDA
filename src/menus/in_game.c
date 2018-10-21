#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"
#include "concatf.h"
#include "display.h"
#include "graphic.h"
#include "utils.h"

void	execAction(Object obj)
{
	Character	*player = getPlayer();

	if (obj.solid) {
		switch(player->movement.position) {
		case LEFT:
			player->movement.pos.x = obj.pos.x + 16;
			break;
		case RIGHT:
			player->movement.pos.x = obj.pos.x - 16;
			break;
		case UP:
			player->movement.pos.y = obj.pos.y + 1;
			break;
		case DOWN:
			player->movement.pos.y = obj.pos.y - 33;
			break;
		}
	}
	if (obj.footstepSound > player->stepSound)
		player->stepSound = obj.footstepSound + rand() % obj.footstepVariance;
	switch(obj.action) {
	case DEAL_DAMAGES:
		for (int i = 0; i < DAMAGES_TYPE_NB; i++) {
			if (obj.damages[i] && (player->invulnerabiltyTime <= 0 || obj.damages[i] < 0)) {
				dealDamages(player, obj.damages[i], i);
				player->invulnerabiltyTime = obj.invulnerabiltyTime > player->invulnerabiltyTime ? obj.invulnerabiltyTime : player->invulnerabiltyTime;
			}
		}
		break;
	case CHANGE_MUSIC:
		break;
	case LAUNCH_CUTSCENE:
		break;
	}
}

void	inGame()
{
	Character	*player = getPlayer();

	if (player->movement.speed < 0)
		player->movement.speed = 0;
	moveCharacter(player, (sfVector2f){
		isKeyPressed(getKey(KEY_RIGHT), game.resources.window) - isKeyPressed(getKey(KEY_LEFT), game.resources.window),
		isKeyPressed(getKey(KEY_DOWN), game.resources.window) - isKeyPressed(getKey(KEY_UP), game.resources.window),
	});
	if (game.state.dialogs) {
		image(getSprite(DIALOG_BOX)->sprite, 0, 380, 640, 100);
		displayDialogs();
	}
	for (int i = 0; i < game.state.characters.length; i++) {
		Character	*chara = &((Character *)game.state.characters.content)[i];

		if (chara->stats.life > 10 * chara->stats.lifeMax)
			chara->stats.life = 10 * chara->stats.lifeMax;
		chara->invulnerabiltyTime -= chara->invulnerabiltyTime > 0 ? 1 : 0;
	}

	if (player->movement.pos.x + game.state.cameraPos.x + 8 > 640)
		game.state.cameraPos.x -= 640;
	else if (player->movement.pos.x + game.state.cameraPos.x + 8 < 0)
		game.state.cameraPos.x += 640;
	else if (player->movement.pos.y + game.state.cameraPos.y + 16 > 480)
		game.state.cameraPos.y -= 480;
	else if (player->movement.pos.y + game.state.cameraPos.y + 16 < 0)
		game.state.cameraPos.y += 480;

	displayLowerLayer();
	displayCharacters();
	displayUpperLayer();
	displayHUD();
}
