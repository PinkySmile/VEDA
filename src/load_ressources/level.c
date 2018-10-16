#include "utils.h"
#include "structs.h"
#include "macros.h"
#include "concatf.h"
#include "functions.h"
#include "configParser.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

extern game_t game;

bool	isFolder(char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) < 0)
		return (false);
	return S_ISDIR(path_stat.st_mode);
}

char	**split(char *str, char sep)
{
	char	**result;
	int	len = 2;
	int	buf = 1;

	for (int i = 0; str[i]; len += str[i++] == sep);
	result = malloc(len * sizeof(*result));
	if (result) {
		*result = strdup(str);
		if (!*result) {
			free(result);
			return (NULL);
		}
		for (int i = 0; str[i]; i++)
			if (str[i] == sep) {
				(*result)[i] = '\0';
				result[buf++] = *result + i + 1;
			}
		result[buf] = NULL;
	}
	return (result);
}

bool	is_nbr(char *nbr)
{
	int	i = 0;
	for (; nbr[i] && (nbr[i] == '+' || nbr[i] == '-'); i++);
	for (; nbr[i] && nbr[i] >= '0' && nbr[i] <= '9'; i++);
	if (nbr[i] == '.')
		i++;
	for (; nbr[i] && nbr[i] >= '0' && nbr[i] <= '9'; i++);
	return (nbr[i] == 0);
}

void	showStr(char *str)
{
	for (int i = 0; str[i]; i++) {
		if (str[i] == 127 || str[i] < 32)
			printf("\\0%o", (unsigned char)str[i]);
		else
			printf("%c", str[i]);
	}
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

	printf("%s: Loading %s !\n", INFO_BEG, path);
	if (!line) {
		printf("%s: Couldn't allocate 1B\n", FATAL_BEG);
		exit(EXIT_FAILURE);
	}
	if (!stream) {
		printf("%s: Cannot open %s (%s)\n", ERROR_BEG, path, strerror(errno));
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
			printf("%s: Memory allocation error\n", FATAL_BEG);
			exit(EXIT_FAILURE);
		}
		objs = realloc(objs, sizeof(*objs) * (i + 2));
		if (!objs) {
			printf("%s: Couldn't allocate %liB", FATAL_BEG, (long)sizeof(*objs) * (i + 1));
			exit(EXIT_FAILURE);
		}
		memset(&objs[i], 0, sizeof(*objs) * 2);
		temp = 0;
		for (len = 0; nbrs[len]; len++);
		if (len != 9 + DAMAGES_TYPE_NB) {
			printf("%s: Invalid line %i: \"", ERROR_BEG, i);
			showStr(line);
			printf("\". A line should contain %i elements but %i were found\n", 9 + DAMAGES_TYPE_NB, len);
			free(objs);
			free(line);
			fclose(stream);
			return (NULL);
		}
		for (int j = 0; j < (9 + DAMAGES_TYPE_NB); j++) {
			if (!is_nbr(nbrs[j])) {
				printf("%s: Invalid line %i: col %i \"", ERROR_BEG, i + 2, temp);
				showStr(nbrs[j]);
				printf("\"\n");
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
		objs[i].invulnerabiltyTime	= atof(nbrs[6]);
		objs[i].footstepSound		= atoi(nbrs[7]);
		objs[i].footstepVariance	= atoi(nbrs[8]);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			objs[i].damages[j]	= atoi(nbrs[9 + j]);
		if (objs[i].layer <= 0) {
			printf("%s: Invalid line %i: col %i \"", ERROR_BEG, i + 2, (int)(strlen(nbrs[0]) + strlen(nbrs[1]) + strlen(nbrs[2]) + 3));
			showStr(nbrs[3]);
			printf("\": Expected value greater than 0\n");
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
		if (line[i] == '§')
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
		printf("%s: %s: %s\n", ERROR_BEG, buffer, strerror(errno));
		buff = concatf("%s: %s\n", buffer, strerror(errno));
		dispMsg("Error", buff, 0);
		free(buff);
		return NULL;
	}
	line = malloc(1);
	if (!line) {
		printf("%s: Allocation error\n", ERROR_BEG);
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
	ParserObj	*objBuffer;
	Character	buff;

	if (result.error) {
		buffer = concatf("Error: Cannot load file %s: %s\n", path, result.error);
		dispMsg("Loading error", buffer, 0);
		free(buffer);
	} else if (result.type != ParserListType) {
		buffer = concatf("Error: Cannot load file %s: Invalid type\n", path, result.error);
		dispMsg("Loading error", buffer, 0);
		free(buffer);
		Parser_destroyData(result.data, result.type);
	} else {
		array = ParserList_toArray(result.data);
		if (array.length < 0) {
			buffer = concatf("Error: Cannot load file %s: Invalid array types\n", path);
			dispMsg("Loading error", buffer, 0);
			free(buffer);
		} else if (array.type != ParserObjType) {
			buffer = concatf("Error: Cannot load file %s: Invalid array type\n", path);
			dispMsg("Loading error", buffer, 0);
			free(buffer);
		} else {
			characters.length = array.length;
			characters.content = malloc(array.length * sizeof(Character));
			memset(characters.content, 0, array.length * sizeof(Character));
			for (int i = 0; i < array.length; i++) {
				memset(&buff, 0, sizeof(buff));
				obj = ParserArray_getElement(&array, i);
				objBuffer = ParserObj_getElement(obj, "name");
				if (objBuffer) {
					if (objBuffer->type != ParserStringType)
						printf("%s: Field \"name\" in character %i has an invalid type\n", ERROR_BEG, i);
					else
						strncpy((char *)buff.name, ParserString_toCharStar(objBuffer->data), 32);
				} else
					printf("%s: Character %i has no field \"name\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "sprite_id");
				if (objBuffer) {
					if (objBuffer->type != ParserIntType)
						printf("%s: Field \"sprite_id\" in character %i has an invalid type\n", ERROR_BEG, i);
					else
						buff.texture = ParserInt_toInt(objBuffer->data);
				} else
					printf("%s: Character %i has no field \"sprite_id\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "x_pos");
				if (objBuffer) {
					if (objBuffer->type == ParserFloatType)
				        	buff.movement.pos.x = ParserFloat_toFloat(objBuffer->data);
					else if (objBuffer->type == ParserIntType)
				        	buff.movement.pos.x = ParserInt_toInt(objBuffer->data);
					else
						printf("%s: Field \"x_pos\" in character %i has an invalid type\n", ERROR_BEG, i);
				} else
					printf("%s: Character %i has no field \"x_pos\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "y_pos");
				if (objBuffer) {
					if (objBuffer->type == ParserFloatType)
				        	buff.movement.pos.y = ParserFloat_toFloat(objBuffer->data);
					else if (objBuffer->type == ParserIntType)
				        	buff.movement.pos.y = ParserInt_toInt(objBuffer->data);
					else
						printf("%s: Field \"y_pos\" in character %i has an invalid type\n", ERROR_BEG, i);
				} else
					printf("%s: Character %i has no field \"y_pos\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "max_life");
				if (objBuffer) {
					if (objBuffer->type == ParserFloatType)
				        	buff.stats.lifeMax = ParserFloat_toFloat(objBuffer->data);
					else if (objBuffer->type == ParserIntType)
				        	buff.stats.lifeMax = ParserInt_toInt(objBuffer->data);
					else
						printf("%s: Field \"max_life\" in character %i has an invalid type\n", ERROR_BEG, i);
				} else
					printf("%s: Character %i has no field \"max_life\"\n", WARNING_BEG, i);
				buff.stats.life = buff.stats.lifeMax * 10;
				objBuffer = ParserObj_getElement(obj, "current_life");
				if (objBuffer) {
					if (objBuffer->type == ParserFloatType)
				        	buff.stats.life = ParserFloat_toFloat(objBuffer->data);
					else if (objBuffer->type == ParserIntType)
				        	buff.stats.life = ParserInt_toInt(objBuffer->data);
					else
						printf("%s: Field \"current_life\" in character %i has an invalid type\n", ERROR_BEG, i);
				} else
					printf("%s: Character %i has no field \"current_life\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "max_energy");
				if (objBuffer) {
					if (objBuffer->type == ParserFloatType)
				        	buff.stats.maxEnergy = ParserFloat_toFloat(objBuffer->data);
					else if (objBuffer->type == ParserIntType)
				        	buff.stats.maxEnergy = ParserInt_toInt(objBuffer->data);
					else
						printf("%s: Field \"max_energy\" in character %i has an invalid type\n", ERROR_BEG, i);
				} else
					printf("%s: Character %i has no field \"max_energy\"\n", WARNING_BEG, i);
				buff.stats.energy = buff.stats.maxEnergy * 10;
				objBuffer = ParserObj_getElement(obj, "current_energy");
				if (objBuffer) {
					if (objBuffer->type == ParserFloatType)
				        	buff.stats.energy = ParserFloat_toFloat(objBuffer->data);
					else if (objBuffer->type == ParserIntType)
				        	buff.stats.energy = ParserInt_toInt(objBuffer->data);
					else
						printf("%s: Field \"current_energy\" in character %i has an invalid type\n", ERROR_BEG, i);
				} else
					printf("%s: Character %i has no field \"current_energy\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "battle_info");
				if (objBuffer) {
					if (objBuffer->type != ParserStringType)
						printf("%s: Field \"battle_script\" in character %i has an invalid type\n", ERROR_BEG, i);
					else
				        	buff.battleScript = strdup(ParserString_toCharStar(objBuffer->data));
				} else
					printf("%s: Character %i has no field \"battle_info\"\n", WARNING_BEG, i);
				objBuffer = ParserObj_getElement(obj, "dialogs");
				if (objBuffer) {
					if (objBuffer->type != ParserStringType)
						printf("%s: Field \"dialogs\" in character %i has an invalid type\n", ERROR_BEG, i);
					else if (!isFolder(ParserString_toCharStar(objBuffer->data)))
						printf("%s: In field \"dialogs\" of character %i: %s is not a folder\n", ERROR_BEG, i, ParserString_toCharStar(objBuffer->data));
					else if (!(buff.dialogsStrings = loadDialogs(ParserString_toCharStar(objBuffer->data))))
				        	printf("%s: In field \"dialogs\" of character %i: An error occurred during parsing of %s\n", ERROR_BEG, i, ParserString_toCharStar(objBuffer->data));
				} else
					printf("%s: Character %i has no field \"battle_info\"\n", WARNING_BEG, i);
				buff.movement.canMove = true;
				buff.movement.animationClock = sfClock_create();
				buff.movement.stateClock = sfClock_create();
				buff.stats.energyRegenClock = sfClock_create();
				for (int j = 0; j < DAMAGES_TYPE_NB; j++)
					buff.damageClock[j] = sfClock_create();
				((Character *)characters.content)[i] = buff;
			}
		}
		free(array.content);
		Parser_destroyData(result.data, result.type);

	}
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
		((Character *)game.state.characters.content)[0] = buff;
		buff.movement.animationClock = sfClock_create();
		buff.movement.stateClock = sfClock_create();
		buff.stats.energyRegenClock = sfClock_create();
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			buff.damageClock[j] = sfClock_create();
		((Character *)game.state.characters.content)[1] = buff;
	}
	((Character *)game.state.characters.content)[0].isPlayer = true;
	free(buffer);
}
