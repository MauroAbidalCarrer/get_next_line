/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:23:03 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/03 18:09:08 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include<stdio.h>
ssize_t	ff_read(int fd, char *dest, char *s_buff)
{
	ssize_t	r_size;
	ssize_t	len;
	ssize_t	i;

	r_size = read(fd, dest, BUFFER_SIZE);
	if (r_size < 0)
		return (-1);
	dest[r_size] = 0;
	len = r_size;
	if (n_index(dest))
		len = n_index(dest);
	i = len - 1;
	while (++i < r_size)
//{
//printf("%c|", dest[i]);
		s_buff[i - len] = dest[i];
//}
	 if (len < r_size)
	 	{printf("\n");}
	s_buff[i - len] = 0;
	dest[len] = 0;
//printf("DEST = \"%s\"\nHEAD = \"%s\"\nLEN = %ld\n\n", dest, s_buff, len);
//if (len < BUFFER_SIZE || n_index(dest))
//	printf("\n");
	return (len);
}

char	*get_rest(size_t len, int fd, char *s_buff)
{
	char	*bit;
	char	*rest;
	ssize_t	bit_len;

	bit = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (bit == NULL)
		return (NULL);
	bit_len = ff_read(fd, bit, s_buff);
	if (bit_len == -1 || (len == 0 && bit_len == 0))
	{
		free(bit);
		return (NULL);
	}
	len += bit_len;
	if (bit_len < BUFFER_SIZE || n_index(bit))
	{
		rest = r_join(alloc_line(len) + len - 1, bit, bit_len);
		free(bit);
		return (rest);
	}
	rest = r_join(get_rest(len, fd, s_buff), bit, bit_len);
	free(bit);
	return (rest);
}

char	*get_head(char *prev)
{	
	ssize_t	i;
	char	*head;

	head = prev;
	while (head - prev < BUFFER_SIZE - 1 && !*head)
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
	static char	*prev_reads[1024];
	char	*head;
	char	*rest;
	char	*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	if (prev_reads[fd] == NULL)
		prev_reads[fd] = alloc_line(BUFFER_SIZE);
	if (prev_reads[fd] == NULL)
		return (NULL);
	head = get_head(prev_reads[fd]);
	if (head == NULL)
		return (NULL);
//printf("FD = %d, HEAD before read = \"%s\"\n", fd, head);
	if (n_index(head))
//{
//printf("\n---------------------------------\n");
//printf("LINE = \"%s\"\n", head);
//printf("---------------------------------\n\n\n");
		return (head);
//}
	rest = get_rest(ft_strlen(head), fd, prev_reads[fd]);
	line = NULL;
	if (rest != NULL)
		line = r_join(rest, head, ft_strlen(head)) + 1;
	else
	{
		free(prev_reads[fd]);
		prev_reads[fd] = NULL;
	}
 //printf("---------------------------------\nLINE = \"%s\"\n---------------------------------\n\n\n", line);
	free(head);
	return (line);     
}
