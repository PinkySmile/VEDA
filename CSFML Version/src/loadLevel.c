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

char	**splitLines(char *string)
{
	int	len = 2;
	int	len2 = 2;
	char	*str = strdup(string);
	char	**result = NULL;
	char	separator = '\r';
	bool	win = false;

	for (int i = 0; str[i]; i++)
		if (str[i] == '\r')
			len++;
	for (int i = 0; str[i]; i++)
		if (str[i] == '\n')
			len2++;
	if (len == 2) {
		separator = '\n';
		len = len2;
		printf("%s: Linux: ", INFO);
	} else if (len2 > 2) {
		win = true;
		len = 2;
		printf("%s: Windows: ", INFO);
		for (int i = 0; str[i]; i++)
			if (str[i] == '\r' && str[i + 1] == '\n') {
				len++;
				i++;
			}
	} else
		printf("%s: Mac: ", INFO);
	printf("%i lines\n", len);
	result = malloc(len * sizeof(*result));
	if (!result) {
		printf("Error: Couldn't allocate %liB", (long)(len * sizeof(*result)));
		exit(EXIT_FAILURE);
	}
	result[0] = str;
	len = 1;
	for (int i = 0; str[i]; i++) {
		if (win && str[i] == '\r' && str[i + 1] == '\n') {
			str[i] = '\0';
			result[len++] = &str[i + 2];
		} else if (str[i] == separator) {
			str[i] = '\0';
			result[len++] = &str[i + 1];
		}
	}
	result[len] = NULL;
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
	int		fd;
	struct stat	buffer;
	char		*file_buffer = NULL;
	Object		*objs;
	char		**lines = NULL;

	if (stat(path, &buffer) < 0) {
		perror(path);
		return (NULL);
	}
	file_buffer = malloc(buffer.st_size + 1);
	if (!file_buffer) {
		printf("Error: Couldn't allocate %liB", (long)(buffer.st_size + 1));
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	printf("%s: Loading level %s\n", INFO, path);
	if (fd < 0) {
		printf("%s: %s: %s\n", ERROR, path, strerror(errno));
		return (NULL);
	}
	read(fd, file_buffer, buffer.st_size);
	close(fd);
	objs = malloc(sizeof(*objs));
	memset(objs, 0, sizeof(*objs));
	file_buffer[buffer.st_size] = '\0';
	lines = splitLines(file_buffer);
	*bg = strdup(lines[0]);
	for (int i = 1; lines[i] && strcmp(lines[i], ""); i += (9 + DAMAGES_TYPE_NB)) {
		objs = realloc(objs, sizeof(*objs) * (i / (9 + DAMAGES_TYPE_NB) + 2));
		if (!objs) {
			printf("%s: Couldn't allocate %liB", FATAL, sizeof(*objs) * (i / (9 + DAMAGES_TYPE_NB) + 2));
			exit(EXIT_FAILURE);
		}
		memset(&objs[i / (9 + DAMAGES_TYPE_NB)], 0, sizeof(*objs));
		for (int j = 1; j < (9 + DAMAGES_TYPE_NB); j++)
			if (!lines[i + j]) {
				printf("%s: Unexpected <EOF> after line %i (%s)\n", INFO, i + j, lines[i + j - 1]);
				free(objs);
				free(lines[0]);
				free(lines);
				free(file_buffer);
				return (NULL);
			}
		for (int j = 0; j < (9 + DAMAGES_TYPE_NB); j++)
			if (!is_nbr(lines[i + j])) {
				printf("%s: Invalid line %i (", ERROR, i + j + 1);
				showStr(lines[i + j]);
				printf(")\n");
				free(objs);
				free(lines[0]);
				free(lines);
				free(file_buffer);
				return (NULL);
			}
		objs[i / (9 + DAMAGES_TYPE_NB)].id = atoi(lines[i]);
		objs[i / (9 + DAMAGES_TYPE_NB)].pos.x = atoi(lines[i + 1]);
		objs[i / (9 + DAMAGES_TYPE_NB)].pos.y = atoi(lines[i + 2]);
		objs[i / (9 + DAMAGES_TYPE_NB)].layer = atoi(lines[i + 3]);
		objs[i / (9 + DAMAGES_TYPE_NB)].solid = atoi(lines[i + 4]);
		objs[i / (9 + DAMAGES_TYPE_NB)].action = atoi(lines[i + 5]);
		objs[i / (9 + DAMAGES_TYPE_NB)].invulnerabiltyTime = atof(lines[i + 6]);
		objs[i / (9 + DAMAGES_TYPE_NB)].footstepSound = atof(lines[i + DAMAGES_TYPE_NB + 1]);
		objs[i / (9 + DAMAGES_TYPE_NB)].footstepVariance = atof(lines[i + DAMAGES_TYPE_NB + 2]);
		for (int j = 0; j < DAMAGES_TYPE_NB; j++)
			objs[i / (9 + DAMAGES_TYPE_NB)].damages[j] = atoi(lines[i + 7 + j]);
		if (objs[i / (9 + DAMAGES_TYPE_NB)].layer <= 0) {
			printf("%s: Invalid line %i (", ERROR, i + 4);
			showStr(lines[i + 3]);
			printf("): Expected value greater than 0\n");
			free(objs);
			free(lines[0]);
			free(lines);
			free(file_buffer);
			return (NULL);
		}
		if (objs[i / (9 + DAMAGES_TYPE_NB)].solid != 0 && objs[i / (9 + DAMAGES_TYPE_NB)].solid != 1) {
			printf("%s: Invalid line %i (", ERROR, i + 5);
			showStr(lines[i + 4]);
			printf("): Expected boolean value\n");
			free(objs);
			free(lines[0]);
			free(lines);
			free(file_buffer);
			return (NULL);
		}
		objs[i / (9 + DAMAGES_TYPE_NB) + 1].layer = 0;
	}
	free(lines[0]);
	free(lines);
	free(file_buffer);
	printf("%s: Loading %s !\n", INFO, path);
	return (objs);
}
