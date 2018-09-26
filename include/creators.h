#ifndef __CREATORS_FUNCTIONS_
#define __CREATORS_FUNCTIONS_

#include <SFML/Graphics.h>

sfText			*createText();
char			*getVersion();
void			*my_malloc(size_t size);
sfSprite		*createSfSprite(sfTexture *texture);
sfRenderWindow		*createMainWindow();
sfRenderWindow		*createRenderWindow(sfVideoMode mode, const void *title, sfUint32 style, const sfContextSettings *settings, bool unicode);
sfRectangleShape	*createRectangleShape();

#endif