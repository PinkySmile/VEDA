#ifndef __SPRITE_HEADER_
#define __SPRITE_HEADER_

#include <SFML/Graphics.h>

typedef struct {
	sfSprite	*sprite;
	sfTexture	*texture;
	sfVector2f	size;
	sfIntRect	rect;
} Sprite;

#endif