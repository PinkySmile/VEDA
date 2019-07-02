#ifndef VEDA_CONTEXT_H
#define VEDA_CONTEXT_H

#include <configParser.h>
#include <SFML/Audio.h>
#include <setjmp.h>
#include "data_structures/sprite.h"

#define ERROR_BUFFER_SIZE 4096

typedef struct ContextStruct Context;

bool	loadMusic(ParserObj *obj, void *data, char *err_buffer);
bool	loadSprite(ParserObj *obj, void *data, char *err_buffer);
bool	getInteger(ParserObj *obj, void *data, char *err_buffer);
bool	getBattleType(ParserObj *obj, void *data, char *err_buffer);
bool	getUintVector(ParserObj *obj, void *data, char *err_buffer);
bool	getFloatVector(ParserObj *obj, void *data, char *err_buffer);
bool	loadDialogsFile(ParserObj *obj, void *data, char *err_buffer);
bool	getDuppedString(ParserObj *obj, void *data, char *err_buffer);
bool	getFloatingNumber(ParserObj *obj, void *data, char *err_buffer);
bool	getPositiveInteger(ParserObj *obj, void *data, char *err_buffer);
bool	copyStringInBuffer(ParserObj *obj, void *data, char *err_buffer);
bool	loadBattleLuaScript(ParserObj *obj, void *data, char *err_buffer);
bool	loadProjectilesScript(ParserObj *obj, void *data, char *err_buffer);
bool	getPositiveFloatingNumber(ParserObj *obj, void *data, char *err_buffer);

bool	getObjectElement(Context *context);

typedef enum contextTypes {
	ContextBooleanType	= 1U << 0U,
	ContextStringType	= 1U << 1U,
	ContextFloatType	= 1U << 2U,
	ContextArrayType	= 1U << 3U,
	ContextObjType		= 1U << 4U,
	ContextListType		= 1U << 5U,
	ContextIntType		= 1U << 6U,
	ContextNullType		= 1U << 7U,
} contextTypes;

typedef enum contextActions {
	DO_NOTHING,
	DISPLAY_WARNING,
	LONG_JUMP,
	CALLBACK,
} contextActions;

typedef enum contextIssue {
	MISSING_PARAMETER = 1,
	INVALID_TYPE,
	USAGE_FAILED,
} contextIssue;

typedef struct SpriteLoaded {
	Sprite	sprite;
	bool	needToDestroy;
} SpriteLoaded;

typedef struct MusicLoaded {
	sfMusic	*music;
	bool	needToDestroy;
} MusicLoaded;

struct ContextStruct {
	ParserObj	*object;
	jmp_buf		jumpBuffer;
	char		error[ERROR_BUFFER_SIZE];
	int		expectedType;
	void		*data;
	char		*index;
	contextActions	onMissing;
	contextActions	onInvalidType;
	contextActions	onUseFail;
	void		(*callback)(Context *context, contextIssue issue);
	bool		(*useElement)(ParserObj *obj, void *data, char *err_buffer);
};

#endif //VEDA_CONTEXT_H
