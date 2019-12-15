#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd;
	char *line;

	fd = open ("kk", O_RDONLY);
	while (get_next_line(fd, &line))
		printf("while: %s\n", line);
	//get_next_line(fd, &line);
	printf("last: %s\n", line);
	return (0);
}
