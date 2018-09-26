#include <stdio.h>
#include "destructors.h"
#include "structs.h"
#include "battle_lua.h"

void	destroyStruct()
{
	printf("%s: Destroying sprites\n", INFO);
	destroySprites();

	printf("%s: Destroying sounds\n", INFO);
	destroySounds();

	printf("%s: Destroying buttons\n", INFO);
	destroyButtons();

	printf("%s: Destroying battle instance\n", INFO);
	playSound(NULL, true);
	destroyBattle(game.state.battle_infos);

	printf("%s: Destroying dialog instances\n", INFO);
	destroyDialogs();

	printf("%s: Destroying languages\n", INFO);
	destroyLanguages();

	printf("%s: Destroying characters\n", INFO);
	destroyCharacters();

	printf("%s: Destroying graphic objects\n", INFO);
	destroySfmlObjects();

	printf("%s: Destroying fonts\n", INFO);
	destroyFonts();
}
