#ifndef __GAME_STRUCT_H_
#define __GAME_STRUCT_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

typedef struct {
	void	*content;
	int	lenght;
} Array;

typedef struct {
	sfSprite	*sprite;
	sfTexture	*texture;
} Sprite;

typedef struct {
	sfVector2f	pos;
	int		life;
	int		maxLife;
	int		energy;
	int		maxEnergy;
} Player;

typedef struct game_s game_t;

typedef struct {
	sfVector2f		pos;
	sfRectangleShape	*button;
	void			(*callback)(game_t);
} Button;

struct game_s {
	sfRenderWindow		*window;
	Array			sprites;
	Array			musics;
	Array			sfx;
	sfRectangleShape	*rectangle;
	Player			player;
	Button			*button;
};

#endif