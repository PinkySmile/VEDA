#include <stdio.h>
#include <stdlib.h>

ssize_t	getline(char **lineptr, size_t *n, FILE *stream)
{
	char	*bufptr = NULL;
	char	*buffer = NULL;
	size_t	size;
	ssize_t	index = 0;
	int	character;

	if (!lineptr || !stream || !n)
		return -1;
	bufptr = *lineptr;
	size = *n;
	character = fgetc(stream);
	if (character == EOF)
		return -1;
	if (!bufptr) {
		bufptr = malloc(128);
		if (!bufptr)
			return -1;
		size = 128;
	}
	while (character != EOF) {
		if (index > (int)(size - 1)) {
			size += 128;
			buffer = realloc(bufptr, size);
			if (!buffer) {
				free(bufptr);
				return -1;
			}
			bufptr = buffer;
		}
		bufptr[index++] = character;
		if (character == '\n')
			break;
		character = fgetc(stream);
	}
	bufptr[index++] = '\0';
	*lineptr = bufptr;
	*n = size;
	return index;
}