#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "object.h"
#include "array.h"
#include "character.h"
#include "concatf.h"
#include "utils.h"

void	saveLevel(char *path, Object *objs, char *header, Array characters)
{
	FILE		*stream;
	size_t		len;
	int		fd;
	char		*buffer;
	char		head = SAVED_LEVEL_HEADER;
	Character	*chars = characters.content;

	printf("%s: Saving to %s\n", INFO_BEG, path);
	stream = fopen(path, "wb");
	if (!stream) {
		printf("%s: Cannot open save file (%s: %s)\n", ERROR_BEG, path, strerror(errno));
		buffer = concatf("Cannot open save file (%s: %s)\n", path, strerror(errno));
		dispMsg("Error", buffer, MB_OK | MB_ICONERROR);
		free(buffer);
		return;
	}
	fd = fileno(stream);
	len = strlen(header);
	write(fd, &head, sizeof(head));
	write(fd, &len, sizeof(len));
	write(fd, header, len);
	for (len = 0; objs[len].layer; len++);
	write(fd, &len, sizeof(len));
	write(fd, objs, sizeof(*objs) * len);
	write(fd, &characters.length, sizeof(characters.length));
	write(fd, chars, sizeof(Character) * characters.length);
	for (int i = 0; i < characters.length; i++)
		write(
			fd,
			chars[i].inventory.content,
			chars[i].inventory.length * sizeof(Item)
		);
	fclose(stream);
}