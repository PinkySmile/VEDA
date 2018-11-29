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
		Character	*chara = getCharacter(i);

		chara->stepSound = IRON;
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
