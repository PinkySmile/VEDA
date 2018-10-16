#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "structs.h"
#include "graphic.h"
#include "concatf.h"

void	displayLoadingBar(int step, int maxSteps, int file, int maxFiles, char *status)
{
	sfVector2f	pos2 = {100, 250};
	sfVector2f	size2 = {440 * step / maxSteps, 50};
	sfVector2f	pos = {100, 350};
	sfVector2f	size = {440 * file / maxFiles, 50};
	char		*nbr = concatf("%i/%i", file, maxFiles);

	status = concatf("%s (%i/%i)", status, step, maxSteps);
	if (!nbr || !status)
		exit(EXIT_FAILURE);
	if (game.resources.text) {
		sfText_setColor(game.resources.text, (sfColor){255, 255, 255, 255});
		sfText_setCharacterSize(game.resources.text, 15);
	}
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){150, 150, 150, 255});
	sfRenderWindow_clear(game.resources.window, (sfColor){0, 0, 0, 255});
	rect(pos.x - 5, pos.y - 5, 450, 60);
	rect(pos2.x - 5, pos2.y - 5, 450, 60);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){0, 0, 0, 255});
	rect(pos.x, pos.y, 440, 50);
	rect(pos2.x, pos2.y, 440, 50);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){0, 0, 255, 255});
	rect(pos.x, pos.y, size.x, size.y);
	sfRectangleShape_setFillColor(game.resources.rectangle, (sfColor){0, 255, 0, 255});
	rect(pos2.x, pos2.y, size2.x, size2.y);
	text(status, 320 - strlen(status) / 2 * 6, 310, false);
	text(nbr, 320 - strlen(nbr) / 2 * 7, 410, false);
	if (game.resources.sprites.content && getSprite(ICON)->sprite)
		image(getSprite(ICON)->sprite, 256, 100, 128, 128);
	else if (game.resources.icon.sprite)
		image(game.resources.icon.sprite, 256, 100, 128, 128);
	sfRenderWindow_display(game.resources.window);
	free(nbr);
	free(status);
}