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
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void read_multiple_files(int nb_files, char** paths)
{
	int fds[nb_files];
	for (int i = 0; i < nb_files; i++)
		fds[i] = open(paths[i], O_RDONLY);
	while (1)
	{
		int closed = 0;
		for (int i = 0; i < nb_files; i++)
		{
			if(fds[i] == -2)
			{
				closed++;
				continue ;
			}
			char *line = get_next_line(fds[i]);
			printf("%s", line);
			if (line == NULL)
				fds[i] = -2;
			else
				free(line);
		}
		if (closed == nb_files)
			break ;
	}
}

int main(int ac, char** av)
{
	if (ac == 1)
		read_file(0);
	else if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		read_file(fd);
		if (fd != -1)
			close(fd);
	}
	else
		read_multiple_files(ac - 1,  av + 1);
}
