#include <string.h>

char	*getParentFolder(char *path)
{
	char	parentPath = strdup(path);

	for (int i = strlen(parentPath) - 1; i >= 0; i--)
		if (i == 0)
			return NULL;
		#if defined _WIN32 || defined __WIN32 || defined __WIN32__
		else if (parentPath[i - 1] == '/') {
		#else
		else if (parentPath[i - 1] == '\\') {
		#endif
			parentPath[i] = 0;
			break;
		}
	return parentPath;
}