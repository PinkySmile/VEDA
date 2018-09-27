#include <stdio.h>
#include <malloc.h>
#include "destructors.h"
#include "structs.h"
#include "battle_lua.h"

void	destroyStruct()
{
	printf("%s: Destroying sprites\n", INFO_BEG);
	destroySprites();

	printf("%s: Destroying sounds\n", INFO_BEG);
	destroySounds();

	printf("%s: Destroying buttons\n", INFO_BEG);
	destroyButtons();

	printf("%s: Destroying battle instance\n", INFO_BEG);
	playSound(NULL, true);
	destroyBattle(game.state.battle_infos);

	printf("%s: Destroying dialog instances\n", INFO_BEG);
	destroyDialogs();

	printf("%s: Destroying languages\n", INFO_BEG);
	destroyLanguages();

	printf("%s: Destroying characters\n", INFO_BEG);
	destroyCharacters();

	printf("%s: Destroying graphic objects\n", INFO_BEG);
	destroySfmlObjects();

	printf("%s: Destroying fonts\n", INFO_BEG);
	destroyFonts();

	free(game.version);
}
