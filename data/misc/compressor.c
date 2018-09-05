#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **args)
{
	int		leng = 0;
	int		read_chars = 0;
	struct stat	file_info;
	char		*buffer = 0;
	int		fd = 0;
	int		file = 0;
	FILE		*stream1;
	FILE		*stream2;
	char		len = 0;

	stream1 = fopen("compressed_files", "wb");
	if (!stream1) {
		perror("compressed_files");
		return (EXIT_FAILURE);
	}
	file = fileno(stream1);
	for (int i = 1; i < argc; i++) {
		if (stat(args[i], &file_info) < 0) {
			perror(args[i]);
		} else {
			leng = file_info.st_size;
			buffer = malloc(leng);
			if (buffer == 0) {
				printf("Error couldn't malloc %iB\n", leng);
			} else {
				stream2 = fopen(args[i], "rb");
				if (!stream2) {
					perror(args[i]);
				} else {
					fd = fileno(stream2);
					read_chars = 1;
					while (read_chars != 0)
						read_chars = read(fd, buffer, leng);
					fclose(stream2);
					write(file, buffer, leng);
					write(file, "\n--end", 6);
					len = strlen(args[i]);
					write(file, &len, 1);
					write(file, args[i], len);
				}
				free(buffer);
			}
		}
	}
	fclose(stream1);
	return (EXIT_SUCCESS);
}
