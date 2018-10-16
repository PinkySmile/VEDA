#include <SFML/Graphics.h>
#include <stdio.h>
#include "character.h"
#include "language.h"
#include "array.h"

char		**split(char *str, char separator);
int		get_nbrlen(int nbr);
Character	*getPlayer(Character *characters, int len);
void		setVolumes(Array sounds, float volume);
int		dispMsg(char *title, char *content, int variate);
int		getLanguage(Language *languages, char *lang_id);
void		setFont(sfText *text, sfFont *font);
char		*getButtonContent(int nameId);
float		isKeyPressed(int keyID, sfRenderWindow *window);
char		*getKeyString(unsigned char keyID);
char		*getParentFolder(char *path);
char		*getAbsolutePath(char *path);
char		*getKeyString(unsigned char keyID);
char		*getButtonContent(int nameId);
ssize_t		getline(char **lineptr, size_t *n, FILE *stream);