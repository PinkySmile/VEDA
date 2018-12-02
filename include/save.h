#include <stdbool.h>
#include "settings.h"
#include "array.h"
#include "object.h"

bool		saveGame	(bool level);
void		loadGame	();
void		saveSettings	();
Settings	loadSettings	(void);
Object		*loadSavedMap	(char *path, char **bg);
Object		*loadMapVersion1(int fd, char **bg);
void		saveLevel(char *path, Object *objs, char *header, Array characters);