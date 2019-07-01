#include <stdio.h>
#include <malloc.h>
#include <logger.h>
#include "destructors.h"
#include "structs.h"
#include "battle_lua.h"

void	destroyStruct()
{
	logMsg(LOGGER_DEBUG, "Destroying sprites");
	destroySprites();

	logMsg(LOGGER_DEBUG, "Destroying sounds");
	destroySounds();

	logMsg(LOGGER_DEBUG, "Destroying buttons");
	destroyButtons();

	logMsg(LOGGER_DEBUG, "Destroying battle instance");
	playSound(NULL, true);
	destroyBattle(game.state.battle_infos);

	logMsg(LOGGER_DEBUG, "Destroying dialog instances");
	destroyDialogs();

	logMsg(LOGGER_DEBUG, "Destroying languages");
	destroyLanguages();

	logMsg(LOGGER_DEBUG, "Destroying characters");
	destroyCharacters();

	logMsg(LOGGER_DEBUG, "Destroying graphic objects");
	destroySfmlObjects();

	logMsg(LOGGER_DEBUG, "Destroying fonts");
	destroyFonts();
}
