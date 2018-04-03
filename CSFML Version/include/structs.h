#ifndef __GAME_STRUCT_H_
#define __GAME_STRUCT_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "macros.h"

enum damagesTypes {
	TRUE_DAMAGE,
	FIRE_DAMAGE,
	SHARP_DAMAGE,
	PIERCE_DAMAGE,
	IMPACT_DAMAGE,
	POISON_DAMAGE,
	ELECTRICITY_DAMAGE,
	DAMAGES_TYPE_NB,
};

enum actions {
	NO_ACTION,
	DEAL_DAMAGES,
	CHANGE_MUSIC,
	LAUNCH_CUTSCENE,
};

enum textures {
	MENU_BACKGROUND,
	OBJECTS,
	MALE_CHARACTER,
	FEMALE_CHARACTER,
	CHARACTER0,
	CHARACTER1,
	CHARACTER2,
	CHARACTER3,
	GOD_EATER,
	LIFE_BAR,
	ENERGY_BAR,
};

enum directions {
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

enum state {
	STATIC,
	MOVING,
};

enum fonts {
	ARIAL,
	SOMETHING,
};

enum musics {
	GAME_OVER,
	MACABRE,
	MYSTERIOUS,
	CLAVIER,
	MAIN_MENU_MUSIC,
	EPICBATTLE_START,
	EPICBATTLE_LOOP,
	SQRT1,
	SQRT2,
	EUGRT_FULL,
	EUGRT_START,
	EUGRT_LOOP,
	UMLAUT,
};

enum sfx {
	IRON,
	ERROR_SOUND,
	EXCLAMATION,
	O_o,
	GRASS1,
	GRASS2,
	GRASS3,
	GRASS4,
	DIRT1,
	DIRT2,
	DIRT3,
	DIRT4,
	MUD1,
	MUD2,
	MUD3,
	MUD4,
};

typedef struct {
	void	*content;
	int	length;
} Array;

typedef struct {
	sfSprite	*sprite;
	sfTexture	*texture;
	sfVector2f	size;
	sfIntRect	rect;
} Sprite;

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
	bool	up;
	bool	right;
	bool	down;
	bool	left;
} Directions;

typedef struct {
	bool		isFemale;
	int		animation;
	int		position;
	int		state;
	sfVector2i	pos;
	float		life;
	int		maxLife;
	float		energy;
	int		maxEnergy;
	bool		canMove;
	Directions	blocked;
	sfClock		*animationClock;
	sfClock		*stateClock;
	int		energyClock;
	sfClock		*energyRegenClock;
	int		energyRegen;
	float		energyUsedBySprint;
	float		sprintSpeed;
	int		timeBeforeEnergyUse;
} Player;

typedef struct {
	char	**buttons;
	char	id[256];
	char	*name;
	char	**items;
	char	**keys;
} Language;

typedef struct {
	char		musicVolume;
	char		sfxVolume;
	char		windowMode;
	sfVector2i	windowSize;
	char		keys[NB_OF_KEYS];
	char		lang_id[256];
} Settings;

typedef struct {
	char	*index;
	void	*content;
	char	type;
} Dict;

typedef struct game_s game_t;

typedef struct {
	int		nameId;
	sfVector2f	pos;
	sfVector2f	size;
	sfColor		color;
	void		(*callback)(game_t *, int);
	bool		disabled;
} Button_config;

typedef struct {
	int		texture;
	int		dialog;
	int		variante;
	int		animation;
	int		status;
	sfVector2f	pos;
	sfVector2f	pointToGo;
	float		sprintSpeed;
} Character;

typedef struct {
	char			*content;
	sfVector2f		pos;
	sfVector2f		size;
	sfColor			color;
	void			(*callback)(game_t *, int);
	sfRectangleShape	*rect;
	bool			displayed;
	bool			active;
} Button;

typedef struct {
	int		id;
	bool		solid;
	sfVector2i	pos;
	int		layer;
	int		damages[DAMAGES_TYPE_NB];
	float		invulnerabiltyTime;
	int		action;
	int		footstepSound;
	int		footstepVariance;
} Object;

typedef struct {
	sfTexture	*texture;
	sfSprite	*sprite;
	sfImage		*image;
} Icon;

typedef struct list_s List;

struct list_s {
	void	*data;
	List	*next;
	List	*prev;
};

struct game_s {
	sfRenderWindow		*window;
	int			menu;
	Array			sprites;
	Array			musics;
	Array			sfx;
	Settings		settings;
	sfRectangleShape	*rectangle;
	sfCircleShape		*circle;
	sfText			*text;
	Array			fonts;
	sfVector2f		baseScale;
	sfVector2i		cam;
	Player			player;
	Button			*buttons;
	Icon			icon;
	Language		*languages;
	Object			*map;
	char			*bg;
	sfVector2i		languagesConf;
	bool			debug;
};

#endif
