
char	*get_next_line(int fd);

#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

void read_file(int fd)
{
	char *line;
	while ((line = get_next_line(fd)))
	{
		//printf("%s", line);
		free(line);
	}
	close(fd);
}

int main(int ac, char** av)
{
	if (ac == 1)
		read_file(0);
	else
	{
		int fd = open(av[1], O_RDONLY);
		read_file(fd);
		if (fd != -1)
			close(fd);
	}
}





