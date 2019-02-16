#include <SFML/Graphics.h>
#include "character.h"

void	displayLoadingBar(int step, int maxSteps, int file, int maxFiles, char *status);
void	displayCharacter(Character *character, int id, sfSprite *sprite);
void	displayCharacters();
void	displayLowerLayer();
void	displayUpperLayer();
void	displayHUD();
void	drawLifeBar();
void	drawEnergyBar();
void	displayDialogs();
void	displayDamagesTakenBy(Character *character);
void	createDialog(char *rawStr, Character *character);

void	debug_displayCharacterHitboxs(Character *character);