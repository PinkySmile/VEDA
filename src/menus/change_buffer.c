#include <SFML/Graphics.h>
#include <stdlib.h>
#include <time.h>
#include "graphic.h"
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

void	buf_modif()
{
	sfUint32	*buffer = getCleanedString(game.input.buffer, time(NULL) % 2);

	sfText_setColor(game.ressources.text, (sfColor){255, 255, 255, 255});
	sfText_setCharacterSize(game.ressources.text, 15);
	text((char *)buffer, 10, 10, true);
	free(buffer);
}

void	changeName()
{
	sfUint32	*buffer = getCleanedString(game.input.buffer, time(NULL) % 2);

	sfText_setColor(game.ressources.text, (sfColor){255, 255, 255, 255});
	sfText_setCharacterSize(game.ressources.text, 20);
	text("How do people call you ?", 50, 50, false);
	sfText_setCharacterSize(game.ressources.text, 15);
	sfText_setColor(game.ressources.text, (sfColor){100, 100, 100, 255});
	text((char *)buffer, 100, 100, true);
	free(buffer);
}
