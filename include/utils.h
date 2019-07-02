#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include "data_structures/language.h"
#include "data_structures/array.h"

char		**split(char *str, char separator);
int		get_nbrlen(int nbr);
Character	*getPlayer();
void		setVolumes(Array sounds, float volume);
int		dispMsg(char *title, char *content, int variate);
int		findLanguage(char *lang_id);
int		getLanguageArrayLen();
void		setFont(sfText *text, sfFont *font);
char		*getButtonContent(int nameId);
float		isKeyPressed(unsigned int keyID, sfRenderWindow *window);
char		*getKeyString(unsigned char keyID);
char		*getParentFolder(char *path);
char		*getAbsolutePath(char *path);
ssize_t		getline(char **lineptr, size_t *n, FILE *stream);
int		playSoundEffect(sfSoundBuffer *buffer);
bool		isFolder(char *path);
sfVector2f	getTextSize(const char *str, const sfFont *font, unsigned size);

#ifndef random
#	define random()	rand()
#endif
#ifndef srandom
#	define srandom(seed)	srand(seed)
#endif