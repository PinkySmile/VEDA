#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <logger.h>
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
		logMsg(LOGGER_FATAL, "Couldn't concatenate '%s' with '/buttons.txt'", path_buffer);
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		logMsg(LOGGER_ERROR, "Couldn't open file %s (%s)", buffer, strerror(errno));
		language->buttons = NULL;
	} else {
		n = 1;
		language->buttons = malloc(sizeof(*language->buttons));
		if (!language->buttons) {
			logMsg(LOGGER_FATAL, "Couldn't allocate %liB", (long)sizeof(*language->buttons));
			exit(EXIT_FAILURE);
		}
		language->buttons[0] = malloc(1);
		for (len = 0; getline(&language->buttons[len], &n, stream) >= 0; len++, n = 1) {
			language->buttons = realloc(language->buttons, sizeof(*language->buttons) * (len + 3));
			if (!language->buttons) {
				logMsg(LOGGER_FATAL, "Couldn't allocate %liB", (long)sizeof(*language->buttons) * (len + 3));
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
		logMsg(LOGGER_FATAL, "Couldn't concatenate '%s' with '/items.txt'\n", buffer);
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		logMsg(LOGGER_ERROR, "Couldn't open file %s (%s)", buffer, strerror(errno));
		language->items = NULL;
	} else {
		n = 1;
		language->items = malloc(sizeof(*language->items));
		language->items[0] = malloc(1);
		for (len = 0; getline(&language->items[len], &n, stream) >= 0; len++, n = 1) {
			language->items = realloc(language->items, sizeof(*language->items) * (len + 3));
			if (!language->items) {
				logMsg(LOGGER_FATAL, "Couldn't allocate %liB\n", (long)sizeof(*language->items) * (len + 3));
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
		logMsg(LOGGER_FATAL, "Couldn't concatenate '%s' with '/keys.txt'", buffer);
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		logMsg(LOGGER_ERROR, "Couldn't open file %s (%s)", buffer, strerror(errno));
		language->keys = NULL;
	} else {
		n = 1;
		language->keys = malloc(sizeof(*language->keys));
		language->keys[0] = malloc(1);
		for (len = 0; getline(&language->keys[len], &n, stream) >= 0; len++, n = 1) {
			language->keys = realloc(language->keys, sizeof(*language->keys) * (len + 3));
			if (!language->keys) {
				logMsg(LOGGER_FATAL, "Couldn't allocate %liB", (long)sizeof(*language->keys) * (len + 3));
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
		logMsg(LOGGER_FATAL, "Couldn't concatenate '%s' with '/name.txt'", buffer);
		exit(EXIT_FAILURE);
	}
	stream = fopen(buffer, "r");
	if (!stream) {
		logMsg(LOGGER_ERROR, "Couldn't open file %s (%s)", buffer, strerror(errno));
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
		logMsg(LOGGER_FATAL, "Couldn't concatenate '%s' with 'data/languages/'", path);
		exit(EXIT_FAILURE);
	}
	logMsg(LOGGER_INFO, "Loading language folder %s", path_buffer);
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
		logMsg(LOGGER_ERROR, "Couldn't find the languages directory");
		return (NULL);
	}
	for (dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
		if (dirEntry->d_name[0] != '.') {
			len++;
			paths = realloc(paths, sizeof(*paths) * (len + 1));
			if (!paths) {
				logMsg(LOGGER_FATAL, "Couldn't allocate %liB", (long)sizeof(*paths) * len);
				exit(EXIT_FAILURE);
			}
			paths[len - 1] = strdup(dirEntry->d_name);
		}
	}
	if (len == 0)
		return (NULL);
	languages = malloc(sizeof(*languages) * (len + 1));
	if (!languages) {
		logMsg(LOGGER_FATAL, "Couldn't allocate %liB", (long)sizeof(*languages) * (len + 1));
		exit(EXIT_FAILURE);
	}
	logMsg(LOGGER_INFO, "Loading %i languages", len);
	for (int i = 0; i < len; i++) {
		buffer = concat("Loading languages (", concat(paths[i], ")", false, false), false, true);
		displayLoadingBar(5, MAX_STEPS, i, len, buffer);
		free(buffer);
		languages[i] = createLanguage(paths[i]);
		free(paths[i]);
	}
	free(paths);
	languages[len].name = NULL;
	logMsg(LOGGER_INFO, "Languages loaded !");
	closedir(dir);
	return (languages);
}
