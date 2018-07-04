#include "functions.h"

void	(* const game_functions[])(game_t *game) = {
	&mainMenu,	//0
	&inGame,	//1
	&controls,	//2
	&audio,		//3
	&options,	//4
	&buf_modif,	//5
	&changeName,	//6
	&battle,	//7
};
