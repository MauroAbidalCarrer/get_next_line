char	*get_next_line(int fd);

#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main(int ac, char** av)
{
	(void)ac;
	int fd = open(av[1], O_RDONLY);
	char* line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

