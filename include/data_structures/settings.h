#ifndef __SETTINGS_HEADER_
#define __SETTINGS_HEADER_

#include <SFML/Graphics.h>
#include "macros.h"

typedef struct {
	char		musicVolume;
	char		sfxVolume;
	enum windowMode	windowMode;
	sfVector2u	windowSize;
	unsigned char	keys[NB_OF_KEYS];
	char		lang_id[256];
	sfUint8		playerName[33];
	bool		dispFramerate;
	bool		characterChosed;
	sfVector2f	baseScale;
} Settings;

#endif