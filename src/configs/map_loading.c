#include "save.h"
#include "object.h"

Object	*(*mapLoadingFunctions[SAVED_LEVEL_HEADER + 1])(int fd, char **bg_path) = {
	NULL,
	loadMapVersion1
};
