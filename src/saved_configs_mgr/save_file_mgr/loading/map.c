#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "globals.h"
#include "creators.h"

Object	*loadSavedMap(char *path, char **bg)
{
	FILE	*stream = fopen(path, "rb");
	int	fd = fileno(stream);
	char	head;
	char	currentPath[PATH_MAX];

	if (!getcwd(currentPath, PATH_MAX)) {
		printf("%s: getcwd: %s\n", ERROR_BEG, strerror(errno));
		memset(currentPath, 0, PATH_MAX);
	}
	printf("%s: Loading saved map '%s/%s'\n", INFO_BEG, currentPath, path);
	read(fd, &head, sizeof(head));
	printf("%s: Saved map file version %i (latest is %i)\n", INFO_BEG, head, SAVED_LEVEL_HEADER);
	if (head == 0) {
		printf(
			"%s: %s: Invalid header version: Save file has been created with a too old version (Save v%i is not supported).\n",
			ERROR_BEG,
			path,
			head
		);
		close(fd);
		return NULL;
	} else if (head > SAVED_LEVEL_HEADER) {
		printf(
			"%s: %s: Invalid header version: Client is outdated (Save v%i < Save v%i).\n",
			ERROR_BEG,
			path,
			SAVED_LEVEL_HEADER,
			head
		);
		close(fd);
		return NULL;
	}
	return mapLoadingFunctions[(int)head](fd, bg);
}

Object	*loadMapVersion1(int fd, char **bg)
{
	size_t	len = 0;
	Object	*map;

	read(fd, &len, sizeof(len));
	*bg = my_malloc(len + 1);
	(*bg)[read(fd, *bg, len)] = 0;
	read(fd, &len, sizeof(len));
	map = my_malloc((len + 1) * sizeof(*map));
	read(fd, map, len * sizeof(*map));
	map[len].layer = 0;
	read(fd, &game.state.characters.length, sizeof(game.state.characters.length));
	game.state.characters.content = my_malloc(sizeof(Character) * game.state.characters.length);
	read(fd, game.state.characters.content, sizeof(Character) * game.state.characters.length);
	for (int i = 0; i < game.state.characters.length; i++) {
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			getCharacter(i)->damageClock[j] = sfClock_create();
		getCharacter(i)->movement.animationClock = sfClock_create();
		getCharacter(i)->movement.stateClock = sfClock_create();
		getCharacter(i)->stats.energyRegenClock = sfClock_create();
		getCharacter(i)->inventory.content = my_malloc(getCharacter(i)->inventory.length);
		read(
			fd,
			getCharacter(i)->inventory.content,
			getCharacter(i)->inventory.length * sizeof(Item)
		);
	}
	printf("%s: Loaded map\n", INFO_BEG);
	return (map);
}