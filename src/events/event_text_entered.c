#include <SFML/Graphics.h>
#include "structs.h"

void	manageTextEntered(sfEvent *event)
{
	if (event->text.unicode == 8 && game.input.bufPos > 0)
		game.input.buffer[--game.input.bufPos] = 0;
	else if (event->text.unicode != 8)
		game.input.buffer[game.input.bufPos < game.input.bufSize ? game.input.bufPos++ : game.input.bufPos - 1] = event->text.unicode;
}