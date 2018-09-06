#ifndef __PROJECTILE_HEADER_
#define __PROJECTILE_HEADER_

#include <SFML/Graphics.h>
#include "sprite.h"

typedef struct {
	int		bankID;
	Sprite		sprite;
	sfVector2f	pos;
	sfVector2i	hitbox;
	float		speed;
	float		acceleration;
	int		marker;
	int		animation;
	int		owner;
	float		angle;
	bool		needToDestroySprite;
	int		animSpeed;
	float		rotaSpeed;
	int		maxSpeed;
	int		minSpeed;
	bool		toRemove;
	int		lifeTime;
	sfClock		*clock;
	sfClock		*animClock;
} Projectile;

#endif