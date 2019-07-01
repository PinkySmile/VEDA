#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>
#include <logger.h>
#include "structs.h"

void	destroyCharacters()
{
	for (int i = 0; i < game.state.characters.length; i++) {
		logMsg(LOGGER_DEBUG, "Destroying character %i (%s)", i, getCharacter(i)->name);
		sfClock_destroy(getCharacter(i)->movement.animationClock);
		sfClock_destroy(getCharacter(i)->movement.stateClock);
		sfClock_destroy(getCharacter(i)->stats.energyRegenClock);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			sfClock_destroy(getCharacter(i)->damageClock[j]);
	}
	free(game.state.characters.content);
}

