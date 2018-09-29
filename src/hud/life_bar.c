#include "utils.h"
#include "structs.h"
#include "graphic.h"
#include "macros.h"

void	drawLifeBar()
{
	Character	*player = getPlayer(game.state.characters.content, game.state.characters.length);
	int		lifeBuffer = player->stats.energy;
	int		xPos = 0;
	int		yPos = 0;
	int		currentTier = 0;
	sfIntRect	rec = {0, 0, 16, 16};

	for (int i = 1 ; i <= player->stats.lifeMax ; i++) {
		if (lifeBuffer <= 10 && lifeBuffer > 0)
			rec.left = 48 + 160 * currentTier + 16 * (10 - lifeBuffer);
		else if (lifeBuffer >= 10)
			rec.left = 48 + 160 * currentTier;
		else
			rec.left = 528;
		if (getSprite(LIFE_BAR)->sprite) {
			//Display the content
			sfSprite_setTextureRect(getSprite(LIFE_BAR)->sprite, rec);
			image(getSprite(LIFE_BAR)->sprite, xPos, 465 - yPos, 16, 16);

			//Display the border
			rec.left = 16 * currentTier;
			sfSprite_setTextureRect(getSprite(LIFE_BAR)->sprite, rec);
			image(getSprite(LIFE_BAR)->sprite, xPos, 465 - yPos, 16, 16);
		} else {
			/*
			The sprite is missing ?
			No worries ! I have some sweet rectangles for you.
			*/
			sfRectangleShape_setFillColor(
				game.ressources.rectangle,
				(sfColor){
					currentTier == 0 ? 255 : 0,
					currentTier == 1 ? 255 : 0,
					currentTier == 2 ? 255 : 0,
					255
				});
			if (lifeBuffer <= 10 && lifeBuffer > 0)
				rect(
					xPos,
					465 - yPos + 16 - 16 * lifeBuffer / 10,
					16,
					16 * lifeBuffer / 10
				);
			else if (lifeBuffer >= 10)
				rect(
					xPos,
					465 - yPos,
					16,
					16
				);
		}

		//Offset the X pos
		xPos = xPos + 15;
		if (xPos >= 15 * 10) {
			//We are at the end, reset X and offset Y
			xPos = 0;
			yPos += 15;
			if (yPos >= MAX_HUD_LINES * 15) {
				//We reached the lines limit, increment the tier then
				currentTier++;
				yPos = 0; //Oh and don't forget to reset Y lol
			}
		}
		lifeBuffer = lifeBuffer - 10;
	}
}