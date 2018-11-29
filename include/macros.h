#ifndef __MACROS_H_
#define __MACROS_H_

#include "configParser.h"
#include "enums.h"
#include "display_messagebox.h"

#define INFO_BEG	"[INFO]   "
#define ERROR_BEG	"[ERROR]  "
#define FATAL_BEG	"[FATAL]  "
#define WARNING_BEG	"[WARNING]"

#define BUFFER_MAX_SIZE	100
#define MAX_STEPS	6

#define NB_OF_KEYS	20
#define MAX_HUD_LINES	3

extern struct game_s game;

#define	getCharacter(id)	(id >= 0 && id < game.state.characters.length	? &((Character *)game.state.characters.content)[id]	: NULL)
#define	getSprite(id)		(id >= 0 && id < game.resources.sprites.length	? &((Sprite *)game.resources.sprites.content)[id]	: NULL)
#define	getMusic(id)		(id >= 0 && id < game.resources.musics.length	? ((sfMusic **)game.resources.musics.content)[id]	: NULL)
#define	getSoundEffect(id)	(id >= 0 && id < game.resources.sfx.length	? ((sfSoundBuffer **)game.resources.sfx.content)[id]	: NULL)
#define getLanguage(id)		(id >= 0 && id < getLanguageArrayLen()		? &game.resources.languages[id]				: NULL)
#define isObjectInWindow(obj)	(obj.pos.x + cam.x > -32 && obj.pos.x + cam.x < 672 && obj.pos.y + cam.y > -32 && obj.pos.y + cam.y < 672)
#define getKey(id)		(id >= 0 && id < NB_OF_KEYS ? game.settings.keys[id] : 0)
#define ABS(x)			(x < 0 ? -x : x)

#define PLAYER_SIZE		(sfVector2f){16, 32}
#define PLAYER_HITBOX_OFFSET	(sfVector2f){3,  16}
#define PLAYER_HITBOX_SIZE	(sfVector2f){10, 14}
#define OBJECT_SIZE		(sfVector2f){16, 16}

#define ALLOC_ERROR_MSG		"An error occurred when trying to reserve memory.\n\
If you are playing on a low memory machine, this can cause this kind of error.\n\
Try closing some programs.\n\
More informations can be found in last.log\n\n\
Click OK to close the application"


#define	PARSER_INFOS		((ParserInfos[1]) {{'{', '}', '{', '}', ',', '=', "\"'", "--", NULL, NULL, false, false}})

#define	SAVED_LEVEL_HEADER	1
#define	SAVED_SETTINGS_HEADER	101

#define DEFAULT_KEYS		(unsigned char[NB_OF_KEYS]){\
	sfKeyZ,		\
	sfKeyS,		\
	sfKeyQ,		\
	sfKeyD,		\
	sfKeyI,		\
	sfKeyEscape,	\
	sfKeyF,		\
	sfKeyC,		\
	sfKeyB,		\
	sfKeyP,		\
	sfKeyU,		\
	sfKeyNum1,	\
	sfKeyNum2,	\
	sfKeyNum3,	\
	sfKeyNum4,	\
	sfKeyNum5,	\
	sfKeyNum6,	\
	sfKeyNum7,	\
	sfKeyNum8,	\
	sfKeyLShift	\
}

#define READ_WRITE_RIGHTS	0664

#define ERROR_DEFAULT_FONT	"Error, couldn't load base font '%s'\nIf you are launching the game with a shortcut, try launching the executable itself\nIf it doesn't work, try reinstalling the game.\n"
#define CORRUPTED_SAVE_MSG	"The save file is either corrupted or invalid (too old ?)\n\nDo you want to use the save file anyway ?\nNote that this can make things really glitchy or even crash the game"
#define CORRUPTED_LEVEL		"An error occurred when trying to load level %s.\n\nDo you want to use the save file anyway ?\nNote that this can make things really glitchy or even crash the game"

#endif
