#ifndef __GAME_STRUCT_H_
#define __GAME_STRUCT_H_

#include "enums.h"
#include "character.h"
#include "array.h"
#include "language.h"
#include "settings.h"
#include "button.h"
#include "object.h"
#include "projectile.h"
#include "list.h"
#include "battle.h"
#include "icon.h"
#include "ressources.h"
#include "game_struct.h"

extern	game_t	game;
extern	void	(* const game_functions[])();

#endif
