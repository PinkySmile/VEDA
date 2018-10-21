#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"
#include "macros.h"
#include "structs.h"
#include "concatf.h"
#include "display.h"
#include "functions.h"

int	getLanguageArrayLen()
{
	int	len = 0;

	for (len = 0; game.resources.languages && game.resources.languages[len].name; len++);
	return len;
}

int	findLanguage(char *lang_id)
{
	Language	*languages = game.resources.languages;

	for (int i = 0; languages && languages[i].name; i++)
		if (!strcmp(languages[i].id, lang_id))
			return (i);
	return (-1);
}

void	loadButtonsNames(char *path_buffer, Language *language)
{
	char	*buffer = NULL;
	size_t	n = 1;
	int	len = 1;
	FILE	*stream;
	
	buffer = concat(path_buffer, "/buttons.txt", false, false);
	if (!buffer) {
		printf("%s: Couldn't concatenate '%s' with '%s'\n", FATAL_BEG, buffer, "/name.txt");
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		printf("%s: Couldn't open file %s (%s)\n", ERROR_BEG, buffer, strerror(errno));
		language->buttons = NULL;
	} else {
		n = 1;
		language->buttons = malloc(sizeof(*language->buttons));
		if (!language->buttons) {
			printf("%s: Couldn't allocate %liB\n", FATAL_BEG, (long)sizeof(*language->buttons));
			exit(EXIT_FAILURE);
		}
		language->buttons[0] = malloc(1);
		for (len = 0; getline(&language->buttons[len], &n, stream) >= 0; len++, n = 1) {
			language->buttons = realloc(language->buttons, sizeof(*language->buttons) * (len + 3));
			if (!language->buttons) {
				printf("%s: Couldn't allocate %liB\n", FATAL_BEG, (long)sizeof(*language->buttons) * (len + 3));
				exit(EXIT_FAILURE);
			}
			if (language->buttons[len] && language->buttons[len][strlen(language->buttons[len]) - 1] == '\n')
				language->buttons[len][strlen(language->buttons[len]) - 1] = 0;
			language->buttons[len + 1] = malloc(1);
		}
		language->buttons[len + 1] = NULL;
		fclose(stream);
	}
	free(buffer);
}

void	loadItemsNames(char *path_buffer, Language *language)
{
	char	*buffer = NULL;
	size_t	n = 1;
	int	len = 1;
	FILE	*stream;
	
	buffer = concat(path_buffer, "/items.txt", false, false);
	if (!buffer) {
		printf("%s: Couldn't concatenate '%s' with '%s'\n", FATAL_BEG, buffer, "/name.txt");
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		printf("%s: Couldn't open file %s (%s)\n", ERROR_BEG, buffer, strerror(errno));
		language->items = NULL;
	} else {
		n = 1;
		language->items = malloc(sizeof(*language->items));
		language->items[0] = malloc(1);
		for (len = 0; getline(&language->items[len], &n, stream) >= 0; len++, n = 1) {
			language->items = realloc(language->items, sizeof(*language->items) * (len + 3));
			if (!language->items) {
				printf("%s: Couldn't allocate %liB\n", FATAL_BEG, (long)sizeof(*language->items) * (len + 3));
				exit(EXIT_FAILURE);
			}
			if (language->items[len] && language->items[len][strlen(language->items[len]) - 1] == '\n')
				language->items[len][strlen(language->items[len]) - 1] = 0;
			language->items[len + 1] = malloc(1);
		}
		language->items[len + 1] = NULL;
		fclose(stream);
	}
	free(buffer);
}

void	loadKeysNames(char *path_buffer, Language *language)
{
	char	*buffer = NULL;
	size_t	n = 1;
	int	len = 1;
	FILE	*stream;
	
	buffer = concat(path_buffer, "/keys.txt", false, false);
	if (!buffer) {
		printf("%s: Couldn't concatenate '%s' with '%s'\n", FATAL_BEG, buffer, "/name.txt");
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		printf("%s: Couldn't open file %s (%s)\n", ERROR_BEG, buffer, strerror(errno));
		language->keys = NULL;
	} else {
		n = 1;
		language->keys = malloc(sizeof(*language->keys));
		language->keys[0] = malloc(1);
		for (len = 0; getline(&language->keys[len], &n, stream) >= 0; len++, n = 1) {
			language->keys = realloc(language->keys, sizeof(*language->keys) * (len + 3));
			if (!language->keys) {
				printf("%s: Couldn't allocate %liB\n", FATAL_BEG, (long)sizeof(*language->keys) * (len + 3));
				exit(EXIT_FAILURE);
			}
			if (language->keys[len] && language->keys[len][strlen(language->keys[len]) - 1] == '\n')
				language->keys[len][strlen(language->keys[len]) - 1] = 0;
			language->keys[len + 1] = malloc(1);
		}
		language->keys[len + 1] = NULL;
		fclose(stream);
	}
	free(buffer);
}

void	loadLanguageName(char *path_buffer, Language *language, char *path)
{
	char	*buffer = NULL;
	size_t	n = 0;
	FILE	*stream;
	
	buffer = concat(path_buffer, "/name.txt", false, false);
	if (!buffer) {
		printf("%s: Couldn't concatenate '%s' with '%s'\n", FATAL_BEG, buffer, "/name.txt");
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		printf("%s: Couldn't open file %s (%s)\n", ERROR_BEG, buffer, strerror(errno));
		language->name = strdup(path);
	} else {
		n = 0;
		language->name = NULL;
		getline(&language->name, &n, stream);
		fclose(stream);
	}
	free(buffer);
}

Language	createLanguage(char *path)
{
	Language	language;
	char		*path_buffer = concat("data/languages/", path, false, false);

	memset(&language, 0, sizeof(language));
	if (!path_buffer) {
		printf("%s: Couldn't concatenate '%s' with '%s'\n", FATAL_BEG, "data/languages/", path);
		exit(EXIT_FAILURE);
	}
	printf("%s: Loading language folder %s\n", INFO_BEG, path_buffer);
	strcpy(language.id, path);
	loadButtonsNames(path_buffer, &language);
	loadLanguageName(path_buffer, &language, path);
	loadItemsNames(path_buffer, &language);
	loadKeysNames(path_buffer, &language);
	free(path_buffer);
	return (language);
}

Language	*loadLanguages()
{
	int		len = 0;
	char		*buffer = NULL;
	Language	*languages = NULL;
	char		**paths = NULL;
	DIR		*dir = opendir("data/languages");
	struct dirent	*dirEntry = NULL;

	if (!dir) {
		printf("%s: Couldn't find the languages directory\n", ERROR_BEG);
		return (NULL);
	}
	for (dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
		if (dirEntry->d_name[0] != '.') {
			len++;
			paths = realloc(paths, sizeof(*paths) * (len + 1));
			if (!paths) {
				printf("%s: Couldn't allocate %liB\n", FATAL_BEG, (long)sizeof(*paths) * len);
				exit(EXIT_FAILURE);
			}
			paths[len - 1] = strdup(dirEntry->d_name);
		}
	}
	if (len == 0)
		return (NULL);
	languages = malloc(sizeof(*languages) * (len + 1));
	if (!languages) {
		printf("%s: Couldn't allocate %liB\n", FATAL_BEG, (long)sizeof(*languages) * (len + 1));
		exit(EXIT_FAILURE);
	}
	printf("%s: Loading %i languages\n", INFO_BEG, len);
	for (int i = 0; i < len; i++) {
		buffer = concat("Loading languages (", concat(paths[i], ")", false, false), false, true);
		displayLoadingBar(5, MAX_STEPS, i, len, buffer);
		free(buffer);
		languages[i] = createLanguage(paths[i]);
		free(paths[i]);
	}
	free(paths);
	languages[len].name = NULL;
	printf("%s: Languages loaded !\n", INFO_BEG);
	closedir(dir);
	return (languages);
}
