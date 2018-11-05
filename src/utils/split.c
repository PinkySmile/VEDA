#include <malloc.h>
#include <stddef.h>
#include <string.h>

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
