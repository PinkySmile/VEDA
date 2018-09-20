#include <SFML/Graphics.c>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

extern char	*programPath = NULL;

void	*my_malloc(size_t size)
{
	void	*ptr = malloc(size);

	if (!ptr) {
		puts("Allocation failure");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

sfRenderWindow	*createRenderWindow(sfVideoMode mode, const void *title, sfUint32 style, const sfContextSettings *settings, bool unicode)
{
	sfRenderWindow	*window;

	if (unicode)
		window = sfRenderWindow_createUnicode(mode, title, style, settings);
	else
		window = sfRenderWindow_create(mode, title, style, settings);
	if (!window) {
		printf("%s: Couldn't create window\n", FATAL);
		dispMsg("Window error", "Couldn't create window object", 0);
	}
	return window;
}