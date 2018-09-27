#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include "structs.h"
#include "macros.h"
#include "functions.h"
#include "concatf.h"

void	saveLevel(char *path, Object *objs, char *header)
{
	int	fd;
	char	*buffer = "test";

	printf("%s: Saving to %s\n", INFO_BEG, path);
	fd = open(path, O_WRONLY | O_CREAT, 0664);
	if (fd < 0) {
		printf("%s: Cannot open save file (%s: %s)\n", ERROR_BEG, path, strerror(errno));
		buffer = concatf("Cannot open save file (%s: %s)\n", PATH, strerror(errno));
		dispMsg("Error", buffer, 0);
		free(buffer);
		return;
	}
	write(fd, header, strlen(header));
	for (int i = 0; objs[i].layer; i++) {
		buffer = concatf("\n%i %i %i %i %i %i %f %i %i %i %i %i %i %i %i %i",
			objs[i].id,
			objs[i].pos.x,
			objs[i].pos.y,
			objs[i].layer,
			objs[i].solid,
			objs[i].action,
			objs[i].invulnerabiltyTime,
			objs[i].footstepSound,
			objs[i].footstepVariance,
			objs[i].damages[0],
			objs[i].damages[1],
			objs[i].damages[2],
			objs[i].damages[3],
			objs[i].damages[4],
			objs[i].damages[5],
			objs[i].damages[6]
		);
		write(fd, buffer, strlen(buffer));
		free(buffer);
	}
	close(fd);
}

bool	saveGame(bool level)
{
	int		fd;
	struct stat	st;
	bool		success = false;
	int		len = 0;
	char		*buffer = NULL;
	ParserObj	obj;
	Character	charac;
	ParserList	*result = malloc(sizeof(ParserList));

	printf("%s: Saving game\n", INFO_BEG);
	if (stat("save", &st) == -1) {
		printf("%s: Creating folder \"save\"\n", INFO_BEG);
		#ifdef __MINGW32__
			success = (mkdir("save") == 0);
		#else
			success = (mkdir("save", 0766) == 0);
		#endif
		if (!success) {
			printf("%s: Couldn't create folder \"save\" (%s)\n", ERROR_BEG, strerror(errno));
			buffer = concatf("Couldn't create folder \"save\" (%s)", strerror(errno));
			dispMsg("Error", buffer, 4);
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
		dispMsg("Error", buffer, 0);
		free(buffer);
		return (false);
	}
	len = game.state.loadedMap.path ? strlen(game.state.loadedMap.path) : 0;
	if (write(fd, &len, sizeof(len)) != sizeof(len)) {
		printf("%s: Couldn't write save file\n", ERROR_BEG);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", 0);
		return (false);
	}
	if (write(fd, game.state.loadedMap.path,len) != len) {
		printf("%s: Couldn't write save file\n", ERROR_BEG);
		close(fd);
		dispMsg("Error", "Couldn't write to save file\nNo space on disk ?", 0);
		return (false);
	}
	close(fd);
	if (result) {
		memset(result, 0, sizeof(*result));
		for (int i = 0; i < game.state.characters.length; i++) {
			charac = ((Character *)game.state.characters.content)[i];
			memset(&obj, 0, sizeof(obj));
			ParserObj_addElement(&obj, charac.name, ParserStringType, "name");
			ParserObj_addElement(&obj, &charac.movement.pos.x, ParserFloatType, "x_pos");
			ParserObj_addElement(&obj, &charac.movement.pos.y, ParserFloatType, "y_pos");
			ParserObj_addElement(&obj, &charac.texture, ParserIntType, "sprite_id");
			ParserObj_addElement(&obj, &charac.stats.maxEnergy, ParserFloatType, "max_energy");
			ParserObj_addElement(&obj, &charac.stats.lifeMax, ParserFloatType, "max_life");
			ParserObj_addElement(&obj, &charac.stats.energy, ParserFloatType, "current_energy");
			ParserObj_addElement(&obj, &charac.stats.life, ParserFloatType, "current_life");
			ParserObj_addElement(&obj, charac.battleScript ? charac.battleScript : "", ParserStringType, "battle_info");
			ParserList_addElement(result, &obj, ParserObjType, -1);
		}
		buffer = concatf("%s/characters-save.json", game.state.loadedMap.path);
		Parser_createFile(buffer, result, ParserListType, NULL);
		ParserList_destroy(result);
		free(buffer);
	}
	if (level) {
		buffer = concat(game.state.loadedMap.path, "/level/floor0.sav", false, false);
		remove(buffer);
		saveLevel(buffer, game.state.loadedMap.objects, game.state.loadedMap.backgroundPath);
		free(buffer);
	}
	return (true);
}

void	loadGame()
{
	int		fd;
	bool		use = false;
	char		*buffer;
	int		len = 0;
	struct stat	st;

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
	if (read(fd, &len, sizeof(len)) != sizeof(len) && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> len\n", ERROR_BEG);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
		if (!use)
			return;
	} else if ((game.state.loadedMap.path = malloc(len + 1)) == NULL) {
		printf("%s: Couldn't allocate %iB\n", FATAL_BEG, len + 1);
		exit(EXIT_FAILURE);
	} else if (read(fd, game.state.loadedMap.path, len) != len && !use) {
		printf("%s: Corrupted save file detected: Unexpected <EOF> map\n", ERROR_BEG);
		use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
		if (!use)
			return;
	} else {
		game.state.loadedMap.path[len] = 0;
		buffer = concat(game.state.loadedMap.path, "/level/floor0.sav", false, false);
		if (stat(buffer, &st) != -1) {
			free(game.state.loadedMap.objects);
			game.state.loadedMap.objects = loadMap(buffer, &game.state.loadedMap.backgroundPath);
			free(buffer);
			free(game.state.characters.content);
			buffer = concatf("%s/characters-save.json", game.state.loadedMap.path);
			game.state.characters = loadCharacters(buffer);
			if (game.state.characters.content)
				((Character *)game.state.characters.content)[0].isPlayer = true;
		} else if (stat(game.state.loadedMap.path, &st) != -1) {
			loadLevel(game.state.loadedMap.path);
		} else if (!use) {
			printf("%s: Corrupted save file detected: Saved map not found\n", ERROR_BEG);
			use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
			if (!use) {
				close(fd);
				return;
			}
		}
		if ((!game.state.loadedMap.objects || !game.state.characters.content) && !use) {
			printf("%s: Corrupted save file detected: Saved map has invalid data\n", ERROR_BEG);
			use = (dispMsg("Error", CORRUPTED_SAVE_MSG, 4) == 6);
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
