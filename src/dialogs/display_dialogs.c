#include <SFML/Graphics.h>
#include <string.h>
#include <malloc.h>
#include "structs.h"
#include "graphic.h"
#include "concatf.h"
#include "functions.h"

bool	addCharacter(char c, char **str, bool reallocBuffer)
{
	int	start = 0;
	char	*buffer = str ? *str : NULL;

	if (!str)
		return (false);
	if (!buffer) {
		buffer = malloc(2);
		if (!buffer)
			return (false);
		*str = buffer;
		buffer[0] = c;
		buffer[1] = 0;
		return (true);
	}
	if (reallocBuffer)
		buffer = realloc(buffer, strlen(buffer) + 2);
	if (!buffer)
		return (false);
	for (int i = 0; buffer[i]; i++)
		if (buffer[i] == '\n')
			start = i + 1;
	if (strlen(buffer) - start > 78) {
		for (int i = strlen(buffer) - 1; i >= 0; i--)
			if (buffer[i] == ' ' || buffer[i] == '\t') {
				buffer[i] = '\n';
				break;
			} else if (buffer[i] == '\n')
				break;
	}
	buffer[strlen(buffer) + 1] = 0;
	buffer[strlen(buffer)] = c;
	*str = buffer;
	return (true);
}

void	displayDialogs()
{
	image(getSprite(DIALOG_BOX)->sprite, 0, 380, 640, 100);
	for (int i = 0; i < game.state.dialogs; i++) {
		if (!game.state.dialogsOnScreen[i].displayedText)
			game.state.dialogsOnScreen[i].displayedText = concatf("%s: ", game.state.dialogsOnScreen[i].dialogOwnerName);
		sfText_setCharacterSize(game.resources.text, 15);
		sfText_setColor(game.resources.text, (sfColor){255, 255, 255, 255});
		text(game.state.dialogsOnScreen[i].displayedText, 10, 390, false);
		if (
			game.state.dialogsOnScreen[i].index < (int)strlen(game.state.dialogsOnScreen[i].rawText) - 1 &&
			sfTime_asSeconds(
				sfClock_getElapsedTime(
					game.state.dialogsOnScreen[i].clock
				)
			) > game.state.dialogsOnScreen[i].speed
		) {
			if (game.state.dialogsOnScreen[i].rawText[game.state.dialogsOnScreen[i].index] == '%')
				resolveCommand(&game.state.dialogsOnScreen[i]);
			else
				addCharacter(
					game.state.dialogsOnScreen[i].rawText[
						game.state.dialogsOnScreen[i].index++
					],
					&game.state.dialogsOnScreen[i].displayedText,
					true
				);
			sfClock_restart(game.state.dialogsOnScreen[i].clock);
		}
	}
}
