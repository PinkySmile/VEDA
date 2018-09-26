#ifndef __MACROS_H_
#define __MACROS_H_

#include "configParser.h"
#include "enums.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define INFO	"[INFO]   "
#define ERROR	"[ERROR]  "
#define FATAL	"[FATAL]  "
#define WARNING	"[WARNING]"

#define BUFFER_MAX_SIZE	100
#define MAX_STEPS	6

#define WINDOWED		0
#define FULLSCREEN		1
#define BORDERLESS_WINDOW	2

#define	getSprite(id)		(id > 0 && id < game.ressources.sprites.length ? &((Sprite *)game.ressources.sprites.content)[id] : NULL)

#define	PARSER_INFOS		((ParserInfos[1]) {{'{', '}', '{', '}', ',', '=', "\"'", "--", NULL, NULL, false, false}})

#define READ_WRITE_RIGHTS	0664

#define ERROR_DEFAULT_FONT	"Error, couldn't load base font '%s'\nIf you are launching the game with a shortcut, try launching the executable itself\nIf it doesn't work, try reinstalling the game.\n"
#define CORRUPTED_SAVE_MSG	"The save file is either corrupted or invalid (too old ?)\n\nDo you want to use the save file anyway ?\nNote that this can make things really glitchy or even crash the game"

#define NB_OF_KEYS	20

#endif
