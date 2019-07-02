#include <stdbool.h>
#include "data_structures/array.h"
#include "data_structures/battle.h"
#include "data_structures/button.h"
#include "data_structures/object.h"
#include "data_structures/sprite.h"
#include "configs.h"
#include "data_structures/language.h"

void		initGame	(bool debug);
Array		loadMusics	();
Array		loadSprites	();
Array		loadSfx		();
Array		loadFonts	();
Button		*loadButtons	();
Language	*loadLanguages	();
void		loadVersion();
Array		loadCharacters	(char *path);
Battle		loadBattleScript(char *path);
void		loadLevel	(char *path);
Object		*loadMap	(char *path, char **bg);
Sprite		createSprite	(Sprite_config config);
sfMusic		*createMusic	(Music_config config);
Array		loadProjectiles	(char *path);
char		**loadDialogs	(char *path);