#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <logger.h>
#include "utils.h"
#include "structs.h"
#include "macros.h"
#include "context.h"
#include "concatf.h"
#include "functions.h"
#include "configParser.h"

extern	size_t	copySize;

bool	is_nbr(const char *nbr)
{
	int	i = 0;
	for (; nbr[i] && (nbr[i] == '+' || nbr[i] == '-'); i++);
	for (; nbr[i] && nbr[i] >= '0' && nbr[i] <= '9'; i++);
	if (nbr[i] == '.')
		i++;
	for (; nbr[i] && nbr[i] >= '0' && nbr[i] <= '9'; i++);
	return (nbr[i] == 0);
}

char	*showStr(char *str)
{
	static char result[512];

	*result = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] == 127 || str[i] < 32)
			sprintf(result + strlen(result), "\\0%o", (unsigned char)str[i]);
		else
			sprintf(result + strlen(result), "%c", str[i]);
	}
	return result;
}

Object	*loadMap(char *path, char **bg)
{
	Object	*objs = NULL;
	FILE	*stream = fopen(path, "r");
	char	**nbrs = NULL;
	char	*line = malloc(1);
	size_t	n = 1;
	int	temp = 0;
	int	len = 0;

	logMsg(LOGGER_INFO, "Loading %s !", path);
	if (!line) {
		logMsg(LOGGER_FATAL, "Couldn't allocate 1B");
		exit(EXIT_FAILURE);
	}
	if (!stream) {
		logMsg(LOGGER_ERROR, "Cannot open %s (%s)", path, strerror(errno));
		return (NULL);
	}
	*line = 0;
	if (getline(&line, &n, stream) > 0) {
		if (line[strlen(line) - 2] == '\r')
			line[strlen(line) - 2] = 0;
		else if (line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = 0;
	}
	*bg = line ? strdup(line) : NULL;
	for (int i = 0; getline(&line, &n, stream) > 0; i++) {
		if (line[strlen(line) - 2] == '\r')
			line[strlen(line) - 2] = 0;
		else if (line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = 0;
		nbrs = split(line, ' ');
		if (!nbrs) {
			logMsg(LOGGER_FATAL, "Memory allocation error");
			exit(EXIT_FAILURE);
		}
		objs = realloc(objs, sizeof(*objs) * (i + 2));
		if (!objs) {
			logMsg(LOGGER_FATAL, "Couldn't allocate %liB", (long)sizeof(*objs) * (i + 1));
			exit(EXIT_FAILURE);
		}
		memset(&objs[i], 0, sizeof(*objs) * 2);
		temp = 0;
		for (len = 0; nbrs[len]; len++);
		if (len != 9 + DAMAGES_TYPE_NB) {
			logMsg(
				LOGGER_ERROR,
				"Invalid line %i: \"%s\". A line should contain %i elements but %i were found",
				i,
				showStr(line),
				9 + DAMAGES_TYPE_NB,
				len
			);
			free(objs);
			free(line);
			fclose(stream);
			return (NULL);
		}
		for (int j = 0; j < (9 + DAMAGES_TYPE_NB); j++) {
			if (!is_nbr(nbrs[j])) {
				logMsg(LOGGER_ERROR, "Invalid line %i: col %i \"%s\"", i + 2, temp, showStr(nbrs[j]));
				free(objs);
				free(line);
				fclose(stream);
				return (NULL);
			}
			temp += strlen(nbrs[j]) + 1;
		}
		objs[i].id			= atoi(nbrs[0]);
		objs[i].pos.x			= atoi(nbrs[1]);
		objs[i].pos.y			= atoi(nbrs[2]);
		objs[i].layer			= atoi(nbrs[3]);
		objs[i].solid			= atoi(nbrs[4]);
		objs[i].action			= atoi(nbrs[5]);
		objs[i].invulnerabilityTime	= atof(nbrs[6]);
		objs[i].footstepSound		= atoi(nbrs[7]);
		objs[i].footstepVariance	= atoi(nbrs[8]);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			objs[i].damages[j]	= atoi(nbrs[9 + j]);
		if (objs[i].layer <= 0) {
			logMsg(
				LOGGER_ERROR,
				"Invalid line %i: col %i \"%s\": Expected value greater than 0",
				i + 2,
				(int)(strlen(nbrs[0]) + strlen(nbrs[1]) + strlen(nbrs[2]) + 3),
				showStr(nbrs[3])
			);
			free(objs);
			free(line);
			fclose(stream);
			return (NULL);
		}
		free(*nbrs);
		free(nbrs);
		objs[i + 1].layer = 0;
	}
	free(line);
	fclose(stream);
	return (objs);
}

bool	lineIsValid(const char *line)
{
	bool	cmd = false;

	for (int i = 0; line[i]; i++) {
		if (line[i] == '%')
			cmd = !cmd;
		if (line[i] == '\\' && line[i + 1])
			i++;
	}
	return (!cmd);
}

char	**loadDialogs(char *path)
{
	char	**dialogs = NULL;
	char	*lang = game.settings.lang_id;
	char	buffer[strlen(path) + strlen(lang) + 6];
	char	*buff;
	char	**buf;
	FILE	*stream;
	char	*line;
	size_t	n = 1;

	sprintf(buffer, "%s/%s.txt", path, lang);
	stream = fopen(buffer, "r");
	if (stream == NULL) {
		logMsg(LOGGER_ERROR, "%s: %s", buffer, strerror(errno));
		buff = concatf("%s: %s\n", buffer, strerror(errno));
		dispMsg("Error", buff, MB_OK | MB_ICONWARNING);
		free(buff);
		return NULL;
	}
	line = malloc(1);
	if (!line) {
		logMsg(LOGGER_ERROR, "Allocation error");
		return (NULL);
	}
	for (int i = 1; getline(&line, &n, stream) > 0; i++) {
		buf = realloc(dialogs, sizeof(*dialogs) * (i + 1));
		if (!buf) {
			free(line);
			for (int j = 0; j < i - 1; j++)
				free(dialogs[i]);
			free(dialogs);
			return (NULL);
		}
		dialogs = buf;
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = 0;
		if (line[strlen(line) - 1] == '\r')
			line[strlen(line) - 1] = 0;
		dialogs[i - 1] = line;
		if (!lineIsValid(line)) {
			for (int j = 0; j < i; j++)
				free(dialogs[i]);
			free(dialogs);
			return (NULL);
		}
		dialogs[i] = NULL;
	}
	free(line);
	return (dialogs);
}

Array	loadCharacters(char *path)
{
	Array		characters = {NULL, 0};
	ParserResult	result = Parser_parseFile(path, NULL);
	ParserArray	array;
	ParserObj	*obj;
	char		*buffer = NULL;
	Character	buff;
	Context		context;
	int		i = 0;

	if (result.error) {
		buffer = concatf("Error: Cannot load file %s: %s\n", path, result.error);
		dispMsg("Loading error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return (Array){NULL, -1};
	} else if (result.type != ParserListType) {
		buffer = concatf("Error: Cannot load file %s: Invalid type\n", path, result.error);
		dispMsg("Loading error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};
	}

	array = ParserList_toArray(result.data);
	if (array.length < 0) {
		buffer = concatf("Error: Cannot load file %s: Inconsistent types in array\n", path);
		dispMsg("Loading error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		free(array.content);
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};
	} else if (array.type != ParserObjType) {
		buffer = concatf("Error: Cannot load file %s: Invalid array type\n", path);
		dispMsg("Loading error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		free(array.content);
		Parser_destroyData(result.data, result.type);
		return (Array){NULL, -1};
	}

	if (setjmp(context.jumpBuffer)) {
		Parser_destroyData(result.data, result.type);
		logMsg(LOGGER_ERROR, "%s: %s", path, context.error);
		buffer = concatf(
			"Error: File '%s' contains invalid data:\nCharacter number %i\n%s\n",
			path,
			i + 1,
			context.error
		);
		dispMsg("Battle Error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return (Array){NULL, -1};
	}

	context.onMissing = DISPLAY_WARNING;
	context.onInvalidType = LONG_JUMP;
	context.onUseFail = LONG_JUMP;
	characters.length = array.length;
	characters.content = malloc(array.length * sizeof(Character));
	memset(characters.content, 0, array.length * sizeof(Character));

	for (; i < array.length; i++) {
		obj = ParserArray_getElement(&array, i);
		memset(&buff, 0, sizeof(buff));
		context.object = obj;

		copySize = 32;
		context.data = &buff.name;
		context.index = "name";
		context.useElement = copyStringInBuffer;
		context.expectedType = ContextStringType;
		getObjectElement(&context);

		context.data = &buff.texture;
		context.index = "sprite_id";
		context.useElement = getPositiveInteger;
		context.expectedType = ContextIntType;
		getObjectElement(&context);
		if (buff.texture + MALE_CHARACTER >= game.resources.sprites.length || buff.texture + MALE_CHARACTER < 0)
			buff.texture = MALE_CHARACTER;

		context.data = &buff.movement.pos;
		context.index = "position";
		context.useElement = getFloatVector;
		context.expectedType = ContextObjType;
		getObjectElement(&context);

		context.data = &buff.stats.lifeMax;
		context.index = "max_life";
		context.useElement = getPositiveInteger;
		context.expectedType = ContextIntType;
		getObjectElement(&context);
		buff.stats.life = buff.stats.lifeMax * 10;

		context.data = &buff.stats.life;
		context.index = "current_life";
		context.useElement = getPositiveInteger;
		context.expectedType = ContextIntType;
		getObjectElement(&context);

		context.data = &buff.stats.maxEnergy;
		context.index = "max_energy";
		context.useElement = getPositiveInteger;
		context.expectedType = ContextIntType;
		getObjectElement(&context);
		buff.stats.energy = buff.stats.maxEnergy * 10;

		context.data = &buff.stats.energy;
		context.index = "current_energy";
		context.useElement = getPositiveInteger;
		context.expectedType = ContextIntType;
		getObjectElement(&context);

		copySize = PATH_MAX;
		context.data = &buff.battleScript;
		context.index = "battle_info";
		context.useElement = copyStringInBuffer;
		context.expectedType = ContextStringType;
		getObjectElement(&context);

		context.data = &buff.dialogsStrings;
		context.index = "dialogs";
		context.useElement = loadDialogsFile;
		context.expectedType = ContextStringType;
		getObjectElement(&context);

		buff.movement.canMove = true;
		buff.movement.animationClock = sfClock_create();
		buff.movement.stateClock = sfClock_create();
		buff.stats.energyRegenClock = sfClock_create();
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			buff.damageClock[j] = sfClock_create();
		((Character *)characters.content)[i] = buff;
	}

	free(array.content);
	Parser_destroyData(result.data, result.type);

	return (characters);
}

void	loadLevel(char *path)
{
	char	*buffer = concatf("%s/level/floor0.lvl", path);

	free(game.state.loadedMap.objects);
	game.state.loadedMap.objects = loadMap(buffer, &game.state.loadedMap.backgroundPath);
	free(buffer);
	free(game.state.characters.content);
	buffer = concatf("%s/characters.chr", path);
	game.state.characters = loadCharacters(buffer);
	if (!game.state.characters.content) {
		Character buff;

		game.state.characters.content = malloc(sizeof(Character) * 2);
		game.state.characters.length = 2;
		memset(&buff, 0, sizeof(buff));
		buff.movement.animationClock = sfClock_create();
		buff.movement.stateClock = sfClock_create();
		buff.stats.energyRegenClock = sfClock_create();
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			buff.damageClock[j] = sfClock_create();
		*getCharacter(0) = buff;
		buff.movement.animationClock = sfClock_create();
		buff.movement.stateClock = sfClock_create();
		buff.stats.energyRegenClock = sfClock_create();
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			buff.damageClock[j] = sfClock_create();
		*getCharacter(1) = buff;
	}
	getCharacter(0)->isPlayer = true;
	free(buffer);
}
