#include <SFML/Graphics.h>
#include <display.h>
#include "structs.h"
#include "graphic.h"

void	debug_displayCharacterHitboxs(Character *character)
{
	sfVector2i	cam = game.state.cameraPos;

	sfRectangleShape_setOutlineThickness(game.resources.rectangle, 1);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){0, 0, 0, 0});
	sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){0, 0, 0, 255});
	rect(
		character->movement.pos.x + cam.x,
		character->movement.pos.y + cam.y,
		PLAYER_SIZE.x - 1,
		PLAYER_SIZE.y - 1
	);
	sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){0, 255, 0, 255});
	rect(
		character->movement.pos.x + cam.x + character->movement.blocked.right,
		character->movement.pos.y + cam.y + PLAYER_HITBOX_OFFSET.y,
		0,
		PLAYER_HITBOX_SIZE.y
	);
	rect(
		character->movement.pos.x + cam.x - character->movement.blocked.left,
		character->movement.pos.y + cam.y + PLAYER_HITBOX_OFFSET.y,
		0,
		PLAYER_HITBOX_SIZE.y
	);
	rect(
		character->movement.pos.x + cam.x + PLAYER_HITBOX_OFFSET.x,
		character->movement.pos.y + cam.y + character->movement.blocked.down,
		PLAYER_HITBOX_SIZE.x,
		0
	);
	rect(
		character->movement.pos.x + cam.x + PLAYER_HITBOX_OFFSET.x,
		character->movement.pos.y + cam.y - character->movement.blocked.up,
		PLAYER_HITBOX_SIZE.x,
		0
	);
	sfRectangleShape_setOutlineColor(game.resources.rectangle, (sfColor){255, 0, 0, 255});
	rect(
		character->movement.pos.x + cam.x + PLAYER_HITBOX_OFFSET.x,
		character->movement.pos.y + cam.y + PLAYER_HITBOX_OFFSET.y,
		PLAYER_HITBOX_SIZE.x - 1,
		PLAYER_HITBOX_SIZE.y - 1
	);
	sfRectangleShape_setOutlineThickness(game.resources.rectangle, 0);
}

void	displayCharacter(Character *character, int id, sfSprite *sprite)
{
	sfIntRect	rec = {0, 0, 32, 32};
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
	rec.top = (character->movement.position / 2 + character->movement.state * 2 + character->movement.animation * 2) * 32;
	rec.left = (character->movement.position % 2) * 32;

	//Display the sprite
	if (sprite) {
		sfSprite_setTextureRect(sprite, rec);
		image(sprite, character->movement.pos.x + cam.x, character->movement.pos.y + cam.y, 32, 32);
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

	if (game.debug)
		debug_displayCharacterHitboxs(character);
}

void	displayCharacters()
{
	Character	*buff;
	static int	var = 0;

	for (int i = 0; i < game.state.characters.length; i++) {
		buff = &((Character *)game.state.characters.content)[i];
		if (getSprite(MALE_CHARACTER + buff->texture) && (!buff->invulnerabiltyTime || var % 5 <= 3))
			displayCharacter(buff, i, getSprite(MALE_CHARACTER + buff->texture)->sprite);
		displayDamagesTakenBy(buff);
	}
	var = var >= 4 ? 0 : var + 1;
}