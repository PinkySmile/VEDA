#include <SFML/Graphics.h>
#include <stdio.h>
#include <malloc.h>

void	destroyCharacters()
{
	for (int i = 0; i < game.state.characters.length; i++) {
		if (game.debug)
			printf("%s: Destroying character %i (%s)\n", INFO, i, ((Character *)game.state.characters.content)[i].name);
		sfClock_destroy(((Character *)game.state.characters.content)[i].movement.animationClock);
		sfClock_destroy(((Character *)game.state.characters.content)[i].movement.stateClock);
		sfClock_destroy(((Character *)game.state.characters.content)[i].stats.energyRegenClock);
		free(((Character *)game.state.characters.content)[i].battleScript);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			sfClock_destroy(((Character *)game.state.characters.content)[i].damageClock[j]);
	}
	free(game.state.characters.content);
}

