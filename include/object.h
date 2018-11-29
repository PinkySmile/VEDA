#ifndef __OBJECT_HEADER_
#define __OBJECT_HEADER_

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "enums.h"

typedef struct {
	int		id;
	bool		solid;
	sfVector2i	pos;
	int		layer;
	int		damages[DAMAGES_TYPE_NB];
	float		invulnerabiltyTime;
	int		action;
	enum sfx	footstepSound;
	int		footstepVariance;
} Object;

#endif