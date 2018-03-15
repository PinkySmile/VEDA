#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **args)
{
	int			len = 0;
	int			read_chars = 0;
	struct stat	file_info;
	char		*buffer = 0;
	int			fd = 0;
	int			file = 0;

	file = open("compressed_files", O_WRONLY | O_CREAT, 0766);
	if (file < 0) {
		perror("compressed_files");
		exit(84);
	}
	for (int i = 1; i < argc; i++) {
		if (stat(args[i], &file_info) < 0) {
			perror(args[i]);
		} else {
			len = file_info.st_size;
			buffer = malloc(len);
			if (buffer == 0) {
				printf("Error couldn't malloc %iB\n", len);
			} else {
				fd = open(args[i], O_RDONLY);
				if (fd < 0) {
					perror(args[i]);
				} else {
					read_chars = 1;
					while (read_chars != 0) {
						read_chars = read(fd, buffer, len);
					}
					close(fd);
					write(file, buffer, len);
					write(file, "\n--end\n", 7);
				}
				free(buffer);
			}
		}
	}
	close(file);
}
