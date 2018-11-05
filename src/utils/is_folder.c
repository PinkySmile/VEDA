#include <stdbool.h>
#include <sys/stat.h>

bool	isFolder(char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) < 0)
		return (false);
	return S_ISDIR(path_stat.st_mode);
}