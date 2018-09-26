#include <stdbool.h>
#include "array.h"
#include "button.h"
#include "language.h"
#include "configs.h"

void		initGame	(bool debug);
Array		loadMusics	();
Array		loadSprites	();
Array		loadSfx		();
Array		loadFonts	();
Button		*loadButtons	();
Language	*loadLanguages	();
char		*getVersion	();
Array		loadCharacters	(char *path);
Battle		loadBattleScript(char *path);
void		loadLevel	(char *path);
Object		*loadMap	(char *path, char **bg);
Sprite		createSprite	(Sprite_config config);
sfMusic		*createMusic	(Music_config config);