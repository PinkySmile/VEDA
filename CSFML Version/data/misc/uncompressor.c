#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char *str, char *str2, int pos)
{
	if (strlen(str + pos) < strlen(str2)) {
		return (0);
	}
	for (int i = 0; str[pos + i] && i < strlen(str2); i++)
		if (str[pos + i] != str2[i])
			return (0);
	return (1);
}

int main(int argc, char **args)
{
	int			len = 0;
	int			begin = 0;
	int			pos = 0;
	struct stat	file_info;
	char		*buffer = 0;
	int			fd = 0;
	int			file = 0;
	int			file_nb = 0;
	int			cur_file = 0;

	if (argc > 1)
		file_nb = atoi(args[1]);
	if (stat("compressed_files", &file_info) < 0) {
		perror("compressed_files");
		return (84);
	}
	len = file_info.st_size;
	buffer = malloc(len);
	if (buffer == 0) {
		printf("Error couldn't malloc %iB\n", len);
	} else {
		file = open("compressed_files", O_RDONLY);
		if (file < 0) {
			perror("compressed_files");
			exit(84);
		} else {
			printf("%i, %i, %p, %i\n", read(file, buffer, len), file, buffer, len);
			printf("Fetching file n%i\n", file_nb);
			printf("%i : %i && %i\n", cur_file < file_nb && buffer[pos], cur_file < file_nb, buffer[pos]);
			while (pos < len) {
				if (match(buffer, "--end", pos)) {
					printf("Found it !\n");
					if(cur_file >= file_nb - 1) {
						break;
					}
					if (cur_file <= file_nb - 2) {
						begin = pos + 6;
						cur_file++;
					}
				}
				pos++;
			}
			fd = open("file", O_WRONLY | O_CREAT, 0766);
			if (fd < 0) {
				perror("file");
				free(buffer);
				return (84);
			}
			printf("Writing from %i to %i\n", begin, pos);
			write(fd, buffer + begin, pos - begin - 2);
			close(fd);
		}
		free(buffer);
	}
	close(file);
}
