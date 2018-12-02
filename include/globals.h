#include "game_struct.h"

extern	game_t	game;
extern	Object	*(*mapLoadingFunctions[SAVED_LEVEL_HEADER])(int fd, char **bg_path);