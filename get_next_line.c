/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:23:03 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/10 17:34:58 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include<stdio.h>

ssize_t	ft_read(int fd, char *dest, char *s_buff)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	len;
	ssize_t	i;

	len = read(fd, buff, BUFFER_SIZE);
	if (len <= 0)
		return (1);
	buff[len] = 0;
	if (n_index(buff))
		len = n_index(buff);
	i = -1;
	while (++i < len)
		dest[i] = buff[i];
	dest[i] = 0;
	while (buff[i])
	{
		s_buff[i - len] = buff[i];
		i++;
	}
	s_buff[i] = 0;
	return (len);
}

char	*get_rest(size_t len, int fd, char *s_buff)
{
	size_t	i;
	char	bit[BUFFER_SIZE + 1];
	ssize_t	bit_len;

	bit_len = ft_read(fd, s_buff, bit);
	if (!bit_len)
		return (NULL);
	len += bit_len;
	if (bit_len < BUFFER_SIZE)
		return (r_join(new_str(len) + len, bit, bit_len));
	return (r_join(get_rest(len, fd, s_buff), bit, bit_len));
}

char	*get_head(char *prev)
{
	size_t	i;
	char	*head;

	head = prev;
	while (!*head && head - prev < BUFFER_SIZE)
		head++;
	i = n_index(head);
	if (!i)
		i = head - prev;
	head = malloc(sizeof(char) * (i + 1));
	if (head == NULL)
		return (NULL);
	head[i] = 0;
	while (--i >= 0)
	{
		head[i] = prev[i];
		prev[i] = 0;
	}
	return (head);
}

char	*get_next_line(int fd)
{
	static char	prev_read[1024][BUFFER_SIZE + 1];
	char	*head;
	char	*rest;
	char	*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	head = get_head(prev_read[fd]);
	if (head == NULL)
		return (NULL);
	if (n_index(head))
		return (head);
	rest = get_rest(ft_strlen(head), fd, prev_read[fd]);
	line = r_join(rest, head, ft_strlen(head));
	free(head);
	return (line);     
}

#include<fcntl.h>
int main(int ac, char** av)
{
	static char buff1[BUFFER_SIZE + 1];
	static char buff2[BUFFER_SIZE + 1];
	int fd = open("salut", O_RDONLY);
	printf("buff1 = %s\n", buff1);
	printf("buff2 = %s\n", buff2);
	printf("ft_read = %li\n", ft_read(fd, buff1, buff2));
	printf("buff1 = %s\n", buff1);
	printf("buff2 = %s\n", buff2);
	close(fd);
}
