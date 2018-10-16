#ifndef __CHARACTER_HEADER_
#define __CHARACTER_HEADER_

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "enums.h"
#include "macros.h"
#include "array.h"

typedef struct {
	int	dialogId;
	int	dialogNum;
	int	variante;
} Dialog;

typedef struct {
	int	id;
	int	ability;
	int	damages[DAMAGES_TYPE_NB];
	double	resistances[DAMAGES_TYPE_NB];
	double	durability;
	double	baseResistances[DAMAGES_TYPE_NB];
	double	baseDurability;
	char	*name;
	int	type;
} Item;

typedef struct {
	unsigned int	up;
	unsigned int	right;
	unsigned int	down;
	unsigned int	left;
} Directions;

typedef	struct {
	int		resistances[DAMAGES_TYPE_NB];
	float		energy;
	int		maxEnergy;
	float		life;
	int		lifeMax;
	int		energyClock;
	sfClock		*energyRegenClock;
	int		energyRegen;
	float		energyUsedBySprint;
	float		sprintSpeed;
	int		timeBeforeEnergyUse;
} Stats;

typedef struct {
	bool		canMove;
	Directions	blocked;
	sfVector2f	pos;
	int		position;
	int		state;
	int		animation;
	float		speed;
	sfVector2f	pointToGo;
	sfClock		*animationClock;
	sfClock		*stateClock;
} Movement;

typedef struct {
	bool		isPlayer;
	int		texture;
	Movement	movement;
	Stats		stats;
	Array		inventory;
	Item		wornItems[5];
	sfUint8		name[33];
	float		invulnerabiltyTime;
	int		damageDisplay[DAMAGES_TYPE_NB];
	sfClock		*damageClock[DAMAGES_TYPE_NB];
	Dialog		dialogs;
	char		*battleScript;
	char		**dialogsStrings;
	enum sfx	stepSound;
} Character;

void	dealDamages(Character *character, int damages, int damageType);

#endif