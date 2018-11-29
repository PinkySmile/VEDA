#ifndef __MACROS_H_
#define __MACROS_H_

#include "configParser.h"
#include "enums.h"

#define INFO_BEG	"[INFO]   "
#define ERROR_BEG	"[ERROR]  "
#define FATAL_BEG	"[FATAL]  "
#define WARNING_BEG	"[WARNING]"

#define BUFFER_MAX_SIZE	100
#define MAX_STEPS	6

#define NB_OF_KEYS	20
#define MAX_HUD_LINES	3

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

#define MB_USERICON					  128
#define MB_ICONASTERISK 				   64
#define MB_ICONEXCLAMATION				 0x30
#define MB_ICONWARNING					 0x30
#define MB_ICONERROR					   16
#define MB_ICONHAND					   16
#define MB_ICONQUESTION 				   32
#define MB_OK						    0
#define MB_ABORTRETRYIGNORE				    2
#define MB_APPLMODAL					    0
#define MB_DEFAULT_DESKTOP_ONLY 		      0x20000
#define MB_HELP 				       0x4000
#define MB_RIGHT				      0x80000
#define MB_RTLREADING				     0x100000
#define MB_TOPMOST				      0x40000
#define MB_DEFBUTTON1					    0
#define MB_DEFBUTTON2					  256
#define MB_DEFBUTTON3					  512
#define MB_DEFBUTTON4				        0x300
#define MB_ICONINFORMATION				   64
#define MB_ICONSTOP					   16
#define MB_OKCANCEL					    1
#define MB_RETRYCANCEL					    5

#define MB_SETFOREGROUND			      0x10000
#define MB_SYSTEMMODAL					 4096
#define MB_TASKMODAL				       0x2000
#define MB_YESNO					    4
#define MB_YESNOCANCEL					    3
#define MB_ICONMASK					  240
#define MB_DEFMASK					 3840
#define MB_MODEMASK				   0x00003000
#define MB_MISCMASK				   0x0000C000
#define MB_NOFOCUS				   0x00008000
#define MB_TYPEMASK					   15

#define IDOK						    1
#define IDCANCEL					    2
#define IDABORT 					    3
#define IDRETRY 					    4
#define IDIGNORE					    5
#define IDYES						    6
#define IDNO						    7

#define	SAVED_LEVEL_HEADER	1

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
