#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <callbacks.h>
#include "destructors.h"
#include "creators.h"
#include "utils.h"
#include "loading.h"
#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "concatf.h"

void	saveLevel(char *path, Object *objs, char *header, Array characters)
{
	FILE		*stream;
	size_t		len;
	int		fd;
	char		*buffer;
	char		head = SAVED_LEVEL_HEADER;
	Character	*chars = characters.content;

	printf("%s: Saving to %s\n", INFO_BEG, path);
	stream = fopen(path, "wb");
	if (!stream) {
		printf("%s: Cannot open save file (%s: %s)\n", ERROR_BEG, path, strerror(errno));
		buffer = concatf("Cannot open save file (%s: %s)\n", path, strerror(errno));
		dispMsg("Error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return;
	}
	fd = fileno(stream);
	len = strlen(header);
	write(fd, &head, sizeof(head));
	write(fd, &len, sizeof(len));
	write(fd, header, len);
	for (len = 0; objs[len].layer; len++);
	write(fd, &len, sizeof(len));
	write(fd, objs, sizeof(*objs) * len);
	write(fd, &characters.length, sizeof(characters.length));
	write(fd, chars, sizeof(Character) * characters.length);
	for (int i = 0; i < characters.length; i++)
		write(
			fd,
			chars[i].inventory.content,
			chars[i].inventory.length * sizeof(Item)
		);
	fclose(stream);
}

bool	saveGame(bool level)
{
	int		fd;
	struct stat	st;
	bool		success;
	int		len = 0;
	char		*buffer = NULL;

	printf("%s: Saving game\n", INFO_BEG);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO_BEG);
		#if defined _WIN32 || defined __WIN32 || defined __WIN32__
			success = (mkdir("save") == 0);
		#else
			success = (mkdir("save", 0766) == 0);
		#endif
		if (!success) {
			printf("%s: Couldn't create folder \"save\" (%s)\n", ERROR_BEG, strerror(errno));
			buffer = concatf("Couldn't create folder \"save\" (%s)", strerror(errno));
			dispMsg("Error", buffer, MB_YESNO | MB_ICONERROR);
			free(buffer);
			return (false);
		}
	}
	remove("save/game.dat.old");
	rename("save/game.dat", "save/game.dat.old");
	fd = open("save/game.dat", O_WRONLY | O_CREAT, READ_WRITE_RIGHTS);
	if (fd < 0) {
		printf("%s: Cannot open save file (save/game.dat: %s)\n", ERROR_BEG, strerror(errno));
		buffer = concatf("Cannot open save file (save/game.dat: %s)\n", strerror(errno));
		dispMsg("Error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return (false);
	}
	len = game.state.loadedMap.path ? strlen(game.state.loadedMap.path) : 0;
	if (write(fd, &len, sizeof(len)) != sizeof(len)) {
		printf("%s: Couldn't write save file\n", ERROR_BEG);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", MB_OK | MB_ICONERROR);
		return (false);
	}
	if (write(fd, game.state.loadedMap.path, len) != len) {
		printf("%s: Couldn't write save file\n", ERROR_BEG);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", MB_OK | MB_ICONERROR);
		return (false);
	}
	close(fd);
	if (level) {
		buffer = concat(game.state.loadedMap.path, "/level/floor0.sav", false, false);
		remove(buffer);
		saveLevel(buffer, game.state.loadedMap.objects, game.state.loadedMap.backgroundPath, game.state.characters);
		free(buffer);
	}
	return (true);
}

Object	*loadSavedMap(char *path, char **bg)
{
	size_t	len = 0;
	FILE	*stream = fopen(path, "rb");
	int	fd = fileno(stream);
	char	head;
	Object	*map;

	read(fd, &head, sizeof(head));
	if (head < SAVED_LEVEL_HEADER) {
		printf(
			"%s: %s: Invalid header version: Save file has been created with a too old version (Save v%i > Save v%i).\n",
			ERROR_BEG,
			path,
			SAVED_LEVEL_HEADER,
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
