#include "structs.h"
#include "character.h"

Character	*getPlayer()
{
	Character	*array = game.state.characters.content;
	int		len = game.state.characters.length;

	for (int i = 0; i < len; i++)
		if (array[i].isPlayer)
			return (&array[i]);
	return (NULL);
}