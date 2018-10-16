#include "character.h"

Character	*getPlayer(Character *array, int len)
{
	for (int i = 0; i < len; i++)
		if (array[i].isPlayer)
			return (&array[i]);
	return (array);
}