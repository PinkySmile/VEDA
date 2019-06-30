#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "game_struct.h"

void	createDialog(char *rawStr, Character *character)
{
	game.state.dialogsOnScreen = realloc(game.state.dialogsOnScreen, sizeof(*game.state.dialogsOnScreen) * (game.state.dialogs + 1));
	if (!game.state.dialogsOnScreen){
		printf("%s: Cannot create dialog box: Memory allocation error (%lu)\n", FATAL_BEG, sizeof(*game.state.dialogsOnScreen) * (game.state.dialogs + 1));
		exit(EXIT_FAILURE);
	}
	game.state.dialogs++;
	memset(&game.state.dialogsOnScreen[game.state.dialogs - 1], 0, sizeof(*game.state.dialogsOnScreen));
	game.state.dialogsOnScreen[game.state.dialogs - 1].dialogOwnerName = character ? character->name : NULL;
	game.state.dialogsOnScreen[game.state.dialogs - 1].sprite = character ? character->dialogFace : NULL;
	game.state.dialogsOnScreen[game.state.dialogs - 1].sound = character ? sfSound_create() : NULL;
	if (game.state.dialogsOnScreen[game.state.dialogs - 1].sound)
		sfSound_setBuffer(game.state.dialogsOnScreen[game.state.dialogs - 1].sound, character->dialogSound);
	game.state.dialogsOnScreen[game.state.dialogs - 1].rawText = rawStr;
	game.state.dialogsOnScreen[game.state.dialogs - 1].clock = sfClock_create();
	game.state.dialogsOnScreen[game.state.dialogs - 1].speed = 0.1;

}