#include <SFML/Graphics.h>
#include "structs.h"
#include "graphic.h"

void	displayCharacter(Character *character, int id, sfSprite *sprite)
{
	sfIntRect	rec = {0, 0, 16, 32};
	sfVector2i	cam = game.state.cameraPos;

	//Check if the character is out of the screen
	if (character->movement.pos.x + cam.x < -16)
		return;
	if (character->movement.pos.y + cam.y < -32)
		return;
	if (character->movement.pos.x + cam.x > 640)
		return;
	if (character->movement.pos.y + cam.y > 480)
		return;

	//Select the good animation
	rec.top = (character->movement.position / 2 + (character->movement.state * 2) + (character->movement.animation * 2)) * 32;
	rec.left = (character->movement.position % 2) * 32;

	//Display the sprite
	if (sprite) {
		sfSprite_setTextureRect(sprite, rec);
		image(sprite, character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 16, 32);
	} else {
		sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setFillColor(
			game.resources.rectangle,
			(sfColor){
				id * 2 % 256,
				((id * 10) >> 8) * 10 % 256,
				id * 2 % 256,
				255
			});
		rect(character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 16, 32);
	}

	if (game.debug) {
		sfRectangleShape_setOutlineThickness(game.resources.rectangle, 1);
		sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){0, 0, 0, 0});
		sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){0, 0, 0, 255});
		rect(character->movement.pos.x, character->movement.pos.y, PLAYER_SIZE.x - 1, PLAYER_SIZE.y - 1);
		rect(
			character->movement.pos.x + cam.x + character->movement.blocked.right,
			character->movement.pos.y + cam.y,
			0,
			OBJECT_SIZE.y
		);
		rect(
			character->movement.pos.x + cam.x - character->movement.blocked.left,
			character->movement.pos.y + cam.y,
			0,
			OBJECT_SIZE.y
		);
		rect(
			character->movement.pos.x + cam.x,
			character->movement.pos.y + cam.y + character->movement.blocked.down,
			OBJECT_SIZE.x,
			0
		);
		rect(
			character->movement.pos.x + cam.x,
			character->movement.pos.y + cam.y - character->movement.blocked.up,
			OBJECT_SIZE.x,
			0
		);
		sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){255, 0, 0, 255});
		rect(
			character->movement.pos.x + cam.x + PLAYER_HITBOX_OFFSET.x,
			character->movement.pos.y + cam.y + PLAYER_HITBOX_OFFSET.y,
			PLAYER_HITBOX_SIZE.x - 1,
			PLAYER_HITBOX_SIZE.y - 1
		);
	}
}

void	displayCharacters()
{
	Character	buff;
	static int	var = 0;

	for (int i = 0; i < game.state.characters.length; i++) {
		buff = ((Character *)game.state.characters.content)[i];
		if (getSprite(MALE_CHARACTER + buff.texture) && (!buff.invulnerabiltyTime || var % 5 <= 3))
			displayCharacter(&buff, i, getSprite(MALE_CHARACTER + buff.texture)->sprite);
	}
	var = var >= 4 ? 0 : var + 1;
}