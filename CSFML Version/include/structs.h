#ifndef __GAME_STRUCT_H_
#define __GAME_STRUCT_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include "macros.h"

enum textures {
	MENU_BACKGROUND,
};

enum musics {
	MAIN_MENU_MUSIC,
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
	sfVector2f	pos;
	int		life;
	int		maxLife;
	int		energy;
	int		maxEnergy;
} Player;

typedef struct {
	Array	buttons;
	char	id[50];
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
	Language	language;
} Settings;

typedef struct {
	char	*index;
	void	*content;
	char	type;
} Dict;

typedef struct {
	sfText	*text;
	sfFont	*font;
} Text;

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
	char			*content;
	sfVector2f		pos;
	sfVector2f		size;
	void			(*callback)(game_t *, int);
	sfRectangleShape	*rect;
	bool			displayed;
} Button;

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
	Player			player;
	Button			*buttons;
};

#endif
