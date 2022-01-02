/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:23:03 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/02 16:16:39 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include<stdio.h>
ssize_t	fff_read(int fd, char *dest, char *s_buff)
{
	ssize_t	len;
	ssize_t	i;

	len = read(fd, dest, BUFFER_SIZE);
	if (len <= 0)
		return (-1);
	dest[len] = 0;
	if (n_index(dest))
		len = n_index(dest);
	i = len - 1;
	while (++i < BUFFER_SIZE)
		s_buff[i - len] = dest[i];
	dest[i - len] = 0;
	return (len);
}

char	*get_rest(size_t len, int fd, char *s_buff)
{
	char	bit[BUFFER_SIZE + 1];
	ssize_t	bit_len;

	bit_len = fff_read(fd, bit, s_buff);
	if (bit_len == -1)
		return (NULL);
	len += bit_len;
	if (bit_len < BUFFER_SIZE || n_index(bit))
		return (r_join(alloc_line(len), bit, bit_len));
	return (r_join(get_rest(len, fd, s_buff), bit, bit_len));
}

char	*get_head(char *prev)
{	
	ssize_t	i;
	char	*head;

	head = prev;
	while (!*head && head - prev < BUFFER_SIZE)
		head++;
	prev = head;
	i = n_index(head);
	if (!i)
		i = ft_strlen(head);
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
	static char	*prev_reads[FD_SIZE];
	char	*head;
	char	*rest;
	char	*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || BUFFER_SIZE > MAX_BS || fd >=  FD_SIZE)
		return (NULL);
	if (prev_reads[fd] == NULL)
		prev_reads[fd] = alloc_line(BUFFER_SIZE) - BUFFER_SIZE + 1;
	head = get_head(prev_reads[fd]);
	if (head == NULL)
		return (NULL);
	if (n_index(head))
		return (head);
	rest = get_rest(ft_strlen(head), fd, prev_reads[fd]);
	line = NULL;
	if (rest != NULL)
		line = r_join(rest, head, ft_strlen(head)) + 1;
	else
		free(prev_reads[fd]);
	free(head);
	return (line);     
}
