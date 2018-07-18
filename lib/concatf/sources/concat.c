#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char	*concat(char *str1, char *str2, bool free1, bool free2)
{
	char	*result;
	
	if (!str1 || !str2) {		
		if (free1)
			free(str1);
		if (free2)
			free(str2);
		return (NULL);
	}
	result = malloc(strlen(str1) + strlen(str2) + 1);
	if (result) {
		strcpy(result, str1);
		strcat(result, str2);
	}
	if (free1)
		free(str1);
	if (free2)
		free(str2);
	return (result);
}