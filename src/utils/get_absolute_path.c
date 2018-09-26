#include <limits.h>

extern	char	*programPath;

char	*getAbsolutePath(char *path)
{
	static	char	realPath[MAX_PATH + 1024];

	if (!programPath)
		sprintf(realPath, "./%s", path);
	else
		sprintf(realPath, "%s%s", programPath, path);
	return realPath;
}