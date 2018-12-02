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
#include <globals.h>
#include <save.h>
#include "macros.h"
#include "creators.h"
#include "utils.h"
#include "character.h"
#include "object.h"
#include "game_struct.h"

void	loadGame()
{
	int		fd;
	bool		use = false;
	char		*buffer;
	void		*buf;
	unsigned int	len = 0;
	struct	stat	st;
	char		currentPath[PATH_MAX];

	if (!getcwd(currentPath, PATH_MAX)) {
		printf("%s: getcwd: %s\n", ERROR_BEG, strerror(errno));
		memset(currentPath, 0, PATH_MAX);
	}
	printf("%s: Loading game save file '%s/save/game.dat'\n", INFO_BEG, currentPath);
	fd = open("save/game.dat", O_RDONLY);
	if (fd < 0) {
		printf("%s: Cannot open save file (%s/save/game.dat: %s)\n", ERROR_BEG, currentPath, strerror(errno));
		return;
	}
	free(game.state.loadedMap.objects);
	free(game.state.loadedMap.backgroundPath);
	free(game.state.loadedMap.path);
	game.state.loadedMap.objects = NULL;
	if (read(fd, &len, sizeof(len)) != sizeof(len)) {
		printf("%s: Corrupted save file detected: Unexpected <EOF>\n", ERROR_BEG);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, MB_YESNO | MB_ICONWARNING) == IDYES);
		if (!use) {
			close(fd);
			return;
		}
	}
	game.state.loadedMap.path = my_malloc(len + 1);
	if ((unsigned)read(fd, game.state.loadedMap.path, len) != len && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF>\n", ERROR_BEG);
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
	printf("%s: Save file loaded\n", INFO_BEG);
}
