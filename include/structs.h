#ifndef __GAME_STRUCT_H_
#define __GAME_STRUCT_H_
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
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
	ICON,
	LIFE_BAR,
	ENERGY_BAR,
	CUTSCENE,
	MUSICS,
	TRIGGER,
	CROSS,
	DIALOG_BOX,
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

enum keys {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_INVENTORY,
	KEY_PAUSE,
	KEY_INTERACT,
	KEY_ATTACK,
	KEY_ACHIEV,
	KEY_POW,
	KEY_UPGRADE,
	KEY_OB1,
	KEY_OB2,
	KEY_OB3,
	KEY_OB4,
	KEY_OB5,
	KEY_OB6,
	KEY_OB7,
	KEY_OB8,
	KEY_SPRINT,
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
	DANMAKU_MUSIC,
};

enum battles {
	BATTLE_ERROR = -1,
	DANMAKU_BATTLE,
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
	int	dialogId;
	int	dialogNum;
	int	variante;
} Dialog;

typedef struct {
	bool		isPlayer;
	int		texture;
	Movement	movement;
	Stats		stats;
	Array		inventory;
	Item		wornItems[5];
	char		name[33];
	float		invulnerabiltyTime;
	int		damageDisplay[DAMAGES_TYPE_NB];
	sfClock		*damageClock[DAMAGES_TYPE_NB];
	Dialog		dialogs;
	char		*battleScript;
	char		**dialogsStrings;
	enum sfx	stepSound;
} Character;

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
	unsigned char	keys[NB_OF_KEYS];
	char		lang_id[256];
	char		playerName[16];
	bool		dispFramerate;
	bool		characterChosed;
	sfVector2f	baseScale;
} Settings;

typedef struct game_s game_t;

typedef struct {
	int		nameId;
	sfVector2f	pos;
	sfVector2f	size;
	sfColor		color;
	sfColor		textColor;
	void		(*callback)(int);
	bool		disabled;
} Button_config;

typedef struct {
	char			*content;
	sfVector2f		pos;
	sfVector2f		size;
	sfColor			color;
	sfColor			textColor;
	void			(*callback)(int);
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
	enum sfx	footstepSound;
	int		footstepVariance;
} Object;

typedef struct {
	sfTexture	*texture;
	sfSprite	*sprite;
	sfImage		*image;
} Icon;

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

typedef struct list_s list_t;
struct list_s {
	void	*data;
	list_t	*prev;
	list_t	*next;
};

typedef struct {
	enum battles	type;
	Character	boss;
	sfVector2f	bossHitbox;
	Sprite		bossSprite;
	Character	*player;
	sfVector2f	playerHitbox;
	list_t		projectiles;
	Array		projectileBank;
	bool		needToDestroySprite;
	bool		needToDestroyMusic;
	sfMusic		*music;
	char		*name;
	char		*script;
	sfClock		*clock;
	bool		timeStopped;
	int		yieldTime;
	lua_State	*Lua;
	lua_State	*Lua_thread;
} Battle;

typedef struct {
	char		*displayedText;
	char		*dialogOwnerName;
	char		*rawText;
	int		index;
	float		speed;
	sfClock		*clock;
} DialogDisplayed;

typedef struct {
	Icon			icon;
	Button			*buttons;
	Array			sprites;
	Array			musics;
	Array			sfx;
	Array			fonts;
	sfRenderWindow		*window;
	Language		*languages;
	sfRectangleShape	*rectangle;
	sfCircleShape		*circle;
	sfText			*text;
	lua_State		*dialogLuaScript;
} Ressources;

typedef struct {
	sfUint32	buffer[BUFFER_MAX_SIZE + 1];
	int		bufPos;
	int		bufSize;
} Input;

typedef struct {
	Object		*objects;
	Sprite		background;
	char		*backgroundPath;
	char		*path;
} Map;

typedef struct {
	int		menu;
	sfVector2i	cameraPos;
	Array		characters;
	Battle		battle_infos;
	Map		loadedMap;
	int		dialogs;
	DialogDisplayed	*dialogsOnScreen;
	int		menuSelected;
} GameState;

struct game_s {
	bool		debug;
	Ressources	ressources;
	Settings	settings;
	GameState	state;
	Input		input;
	sfVector2i	languagesConf;
};

extern game_t game;
extern	void	(* const game_functions[])();

#endif
