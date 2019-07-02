#ifndef __MACROS_H_
#define __MACROS_H_

#include "configParser.h"
#include "enums.h"
#include "display_messagebox.h"

#define BUFFER_MAX_SIZE	100
#define MAX_STEPS	6

#define NB_OF_KEYS	20
#define MAX_HUD_LINES	3

extern struct game_s game;

#define SOUNDS_BUFFER_SIZE	16
#define PLAYER_SIZE		(sfVector2f){16, 32}
#define PLAYER_HITBOX_OFFSET	(sfVector2f){3,  16}
#define PLAYER_HITBOX_SIZE	(sfVector2f){10, 14}
#define OBJECT_SIZE		(sfVector2f){16, 16}

#define	getCharacter(id)	(id >= 0 && id < game.state.characters.length	? &((Character *)game.state.characters.content)[id]	: NULL)
#define	getSprite(id)		(id >= 0 && id < game.resources.sprites.length	? &((Sprite *)game.resources.sprites.content)[id]	: NULL)
#define	getMusic(id)		(id >= 0 && id < game.resources.musics.length	? ((sfMusic **)game.resources.musics.content)[id]	: NULL)
#define	getSoundEffect(id)	(id >= 0 && id < game.resources.sfx.length	? ((sfSoundBuffer **)game.resources.sfx.content)[id]	: NULL)
#define getLanguage(id)		(id >= 0 && id < getLanguageArrayLen()		? &game.resources.languages[id]				: NULL)
#define isObjectInWindow(obj)	(obj.pos.x + cam.x > -OBJECT_SIZE.x && obj.pos.x + cam.x < 640 + OBJECT_SIZE.x && obj.pos.y + cam.y > -OBJECT_SIZE.y && obj.pos.y + cam.y < 640 + OBJECT_SIZE.y)
#define getKey(id)		(id >= 0 && id < NB_OF_KEYS ? game.settings.keys[id] : 0)
#define ABS(x)			(x < 0 ? -x : x)

#define ALLOC_ERROR_MSG		"An error occurred when trying to reserve memory.\n\
If you are playing on a low memory machine, this can cause this kind of error.\n\
Try closing some programs.\n\
More informations can be found in last.log\n\n\
Click OK to close the application"


#define	PARSER_INFOS		((ParserInfos[1]) {{'{', '}', '{', '}', ',', '=', "\"'", "--", NULL, NULL, false, false}})

#define SAVED_LEVEL_VERSION			2
#define	SAVED_SETTINGS_HEADER			101
#define	SAVE_FILES_MAGIC_NUMBER			0x000042A3
#define	SAVE_FILES_MAGIC_NUMBER_REVERSED	0xA3420000

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
#define CORRUPTED_SAVE_MSG	"The save file is either corrupted or invalid (too old ?)\n\nDo you want to create a new one ?"

#endif
