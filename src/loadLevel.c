#include "structs.h"
#include "macros.h"
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

Object	*loadLevel(char *path, char **bg)
{
	Object	*objs = NULL;
	FILE	*stream = fopen(path, "r");
	char	**nbrs = NULL;
	char	*line = malloc(1);
	size_t	n = 1;
	int	temp = 0;
	int	len = 0;

	printf("%s: Loading %s !\n", INFO, path);
	if (!line) {
		printf("%s: Couldn't allocate 1B\n", FATAL);
		exit(EXIT_FAILURE);
	}
	if (!stream) {
		printf("%s: Cannot open %s (%s)\n", ERROR, path, strerror(errno));
		return (NULL);
	}
	*line = 0;
	;
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
			printf("%s: Memory allocation error\n", FATAL);
			exit(EXIT_FAILURE);
		}
		objs = realloc(objs, sizeof(*objs) * (i + 2));
		if (!objs) {
			printf("%s: Couldn't allocate %liB", FATAL, (long)sizeof(*objs) * (i + 1));
			exit(EXIT_FAILURE);
		}
		memset(&objs[i], 0, sizeof(*objs) * 2);
		temp = 0;
		for (len = 0; nbrs[len]; len++);
		if (len != 9 + DAMAGES_TYPE_NB) {
			printf("%s: Invalid line %i: \"", ERROR, i);
			showStr(line);
			printf("\". A line should contain %i elements but %i were found\n", 9 + DAMAGES_TYPE_NB, len);
			free(objs);
			free(line);
			fclose(stream);
			return (NULL);
		}
		for (int j = 0; j < (9 + DAMAGES_TYPE_NB); j++) {
			if (!is_nbr(nbrs[j])) {
				printf("%s: Invalid line %i: col %i \"", ERROR, i + 2, temp);
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
			printf("%s: Invalid line %i: col %i \"", ERROR, i + 2, strlen(nbrs[0]) + strlen(nbrs[1]) + strlen(nbrs[2]) + 3);
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
	if (nbrs)
		free(*nbrs);
	free(nbrs);
	free(line);
	fclose(stream);
	return (objs);
}
