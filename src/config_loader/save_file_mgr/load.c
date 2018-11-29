#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <concatf.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <destructors.h>
#include <loading.h>
#include <callbacks.h>
#include <sys/stat.h>
#include "macros.h"
#include "creators.h"
#include "utils.h"
#include "character.h"
#include "object.h"
#include "game_struct.h"

Object	*loadSavedMap(char *path, char **bg)
{
	size_t	len = 0;
	FILE	*stream = fopen(path, "rb");
	int	fd = fileno(stream);
	char	head;
	Object	*map;

	read(fd, &head, sizeof(head));
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
	return (map);
}

void	loadGame()
{
	int		fd;
	bool		use = false;
	char		*buffer;
	void		*buf;
	unsigned int	len = 0;
	struct	stat	st;

	printf("%s: Loading game\n", INFO_BEG);
	fd = open("save/game.dat", O_RDONLY);
	if (fd < 0) {
		printf("%s: Cannot open save file (save/game.dat: %s)\n", ERROR_BEG, strerror(errno));
		return;
	}
	free(game.state.loadedMap.objects);
	free(game.state.loadedMap.backgroundPath);
	free(game.state.loadedMap.path);
	game.state.loadedMap.objects = NULL;
	if (read(fd, &len, sizeof(len)) != sizeof(len)) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> len\n", ERROR_BEG);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, MB_YESNO | MB_ICONWARNING) == IDYES);
		if (!use) {
			close(fd);
			return;
		}
	}
	game.state.loadedMap.path = my_malloc(len + 1);
	if ((unsigned)read(fd, game.state.loadedMap.path, len) != len && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> map\n", ERROR_BEG);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, MB_YESNO | MB_ICONWARNING) == IDYES);
		if (!use) {
			close(fd);
			return;
		}
	} else {
		game.state.loadedMap.path[len] = 0;
		buffer = concat(game.state.loadedMap.path, "/level/floor0.sav", false, false);
		if (stat(buffer, &st) != -1) {
			free(game.state.loadedMap.objects);
			destroyCharacters();
			game.state.loadedMap.objects = loadSavedMap(buffer, &game.state.loadedMap.backgroundPath);
			if (game.state.characters.content)
				getCharacter(0)->isPlayer = true;
			if ((!game.state.loadedMap.objects || !game.state.characters.content) && !use) {
				printf("%s: Corrupted save file detected: Saved map has invalid data\n", ERROR_BEG);
				use = (dispMsg("Error", CORRUPTED_SAVE_MSG, MB_YESNO | MB_ICONWARNING) == IDYES);
				if (!use) {
					close(fd);
					return;
				}
			}
		} else if (stat(game.state.loadedMap.path, &st) != -1) {
			loadLevel(game.state.loadedMap.path);
			buf = concatf(CORRUPTED_LEVEL, buffer);
			use = (dispMsg("Error", buf, MB_YESNO | MB_ICONWARNING) == IDYES);
			free(buf);
			if ((!game.state.loadedMap.objects || !game.state.characters.content) && !use)
				backOnTitleScreen(-1);
		} else if (!use) {
			printf("%s: Corrupted save file detected: Saved map not found\n", ERROR_BEG);
			use = (dispMsg("Error", CORRUPTED_SAVE_MSG, MB_YESNO | MB_ICONWARNING) == IDYES);
			if (!use) {
				close(fd);
				return;
			}
		}
		free(buffer);
	}
	close(fd);
	printf("%s: Done\n", INFO_BEG);
}
