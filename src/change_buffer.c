#include <SFML/Graphics.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

sfUint32	*getCleanedString(sfUint32 *str, bool cursor)
{
	sfUint32	*result = malloc(sizeof(*result) * 2);
	int		size = 1;

	if (!result)
		exit(EXIT_FAILURE);
	result[0] = cursor ? '_' : ' ';
	result[1] = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] < ' ') {
			result = realloc(result, sizeof(*result) * (size + 3));
			if (!result)
				exit(EXIT_FAILURE);
			size += 2;
			result[size - 3] = '^';
			result[size - 2] = 64 + str[i];
		} else {
			result = realloc(result, sizeof(*result) * (size + 2));
			if (!result)
				exit(EXIT_FAILURE);
			size++;
			result[size - 2] = str[i];
		}
		result[size - 1] = cursor ? '_' : ' ';
		result[size] = 0;
	}
	return (result);
}

void	buf_modif(game_t *game)
{
	sfUint32	*buffer = getCleanedString(game->buffer, time(NULL) % 2);

	sfText_setColor(game->text, (sfColor){255, 255, 255, 255});
	sfText_setCharacterSize(game->text, 15);
	text((char *)buffer, game, 10, 10, true);
	free(buffer);
}
