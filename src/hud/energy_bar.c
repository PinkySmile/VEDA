#include "utils.h"
#include "structs.h"
#include "graphic.h"
#include "macros.h"

void	drawEnergyBar()
{
	Character	*player = getPlayer();
	int		energyBuffer = player->stats.energy;
	int		xPos = 0;
	int		yPos = 0;
	int		currentTier = 0;
	sfIntRect	rec = {0, 0, 16, 16};

	for (int i = 1 ; i <= player->stats.maxEnergy ; i++) {
		//Select the proper filled shape
		if (energyBuffer <= 10 && energyBuffer > 0)
			rec.left = 48 + 160 * currentTier + 16 * (10 - energyBuffer);
		else if (energyBuffer >= 10)
			//Full
			rec.left = 48 + 160 * currentTier;
		else
			//Empty
			rec.left = 528;
		if (getSprite(ENERGY_BAR)->sprite) {
			//Display the content
			sfSprite_setTextureRect(getSprite(ENERGY_BAR)->sprite, rec);
			image(getSprite(ENERGY_BAR)->sprite, 625 - xPos, 465 - yPos, 16, 16);

			//Display the border
			rec.left = 16 * currentTier;
			sfSprite_setTextureRect(getSprite(ENERGY_BAR)->sprite, rec);
			image(getSprite(ENERGY_BAR)->sprite, 625 - xPos, 465 - yPos, 16, 16);
		} else {
			/*
			The sprite is missing ?
			No worries ! I have some sweet rectangles for you.
			*/
			sfRectangleShape_setFillColor(
				game.resources.rectangle,
				(sfColor){
					currentTier == 0 ? 255 : 0,
					currentTier == 1 ? 255 : 0,
					currentTier == 2 ? 255 : 0,
					255
				}
			);
			 if (energyBuffer >= 10)
				rect(
					625 - xPos,
					465 - yPos,
					16,
					16
				);
			else if (energyBuffer > 0)
				rect(
					625 - xPos,
					465 - yPos + 16 * (energyBuffer / 10 - 1),
					16,
					16 * energyBuffer / 10
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
		energyBuffer -= 10;
	}
}