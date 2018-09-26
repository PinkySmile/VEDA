#include <limits.h>
#include <stdio.h>

extern	char	*programPath;

char	*getAbsolutePath(char *path)
{
	static	char	realPath[PATH_MAX + 1024];

	if (!programPath)
		sprintf(realPath, "./%s", path);
	else
		sprintf(realPath, "%s%s", programPath, path);
	return realPath;
}