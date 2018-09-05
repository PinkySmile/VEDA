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
	int		leng = 0;
	int		begin = 0;
	int		pos = 0;
	struct stat	file_info;
	char		*buffer = 0;
	int		fd = 0;
	int		file = 0;
	int		file_nb = 0;
	int		cur_file = 0;
	FILE		*stream1;
	FILE		*stream2;
	char		len = 0;
	char		*name = NULL;

	if (argc > 1)
		file_nb = atoi(args[1]);
	if (stat("compressed_files", &file_info) < 0) {
		perror("compressed_files");
		return (EXIT_FAILURE);
	}
	leng = file_info.st_size;
	buffer = malloc(leng);
	if (!buffer) {
		printf("Error couldn't malloc %iB\n", leng);
		return (EXIT_FAILURE);
	}
	stream1 = fopen("compressed_files", "rb");
	if (!stream1) {
		perror("compressed_files");
		return (EXIT_FAILURE);
	}
	file = fileno(stream1);
	printf("%i, %i, %p, %i\n", read(file, buffer, leng), file, buffer, leng);
	printf("Fetching file n°%i\n", file_nb);
	while (pos < leng) {
		if (match(buffer, "\n--end", pos)) {
			printf("Found it !\n");
			len = buffer[pos + 6];
			if(cur_file >= file_nb - 1) {
				name = malloc(len);
				if (!name) {
					printf("Error couldn't alloc %iB\n", len);
					return (EXIT_FAILURE);
				}
				for (int i = 0; i < len && buffer[pos + 7 + i]; i++)
					name[i] = buffer[pos + 7 + i];
				name[len] = 0;
				break;
			} else if (cur_file <= file_nb - 2) {
				begin = pos + 7 + len;
				cur_file++;
			}
		}
		pos++;
	}
	stream2 = fopen(name, "wb");
	if (!stream2) {
		perror(name);
		free(buffer);
		return (EXIT_FAILURE);
	}
	fd = fileno(stream2);
	printf("Writing from %i to %i\n", begin, pos);
	write(fd, buffer + begin, pos - begin - 2);
	fclose(stream2);
	fclose(stream1);
	free(buffer);
}
