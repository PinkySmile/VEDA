#ifndef __GLOBALS_HEADER_
#define __GLOBALS_HEADER_

#include <stdbool.h>

typedef struct {
	char		*path;
	bool		isRepeated;
} Music_config;

typedef struct {
	char		*path;
	sfVector2f	scale;
	sfVector2i	size;
	sfVector2i	rectPos;
} Sprite_config;

typedef struct {
	int		nameId;
	sfVector2f	pos;
	sfVector2f	size;
	sfColor		color;
	sfColor		textColor;
	void		(*callback)(int);
	bool		disabled;
} Button_config;

extern const Button_config	button_config[];
extern const Sprite_config	sprites_conf[];
extern const char		*fonts_conf[];
extern const Music_config	musics_conf[];
extern const Music_config	sfx_conf[];

#endif