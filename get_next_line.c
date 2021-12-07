/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:23:03 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/06 23:20:22 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	get_back(int fd, size_t already_read)
{
	ssize_t read_ret;
	size_t	currently_read;
	char 	buff[BUFFER_SIZE];

	currently_read = 0;
	while (currently_read < already_read)
	{
		read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret <= 0)
			return (1);
		currently_read += (size_t)read_ret;
	}
	return (0);
}

void	free_lst(t_node *n)
{
	free(n->str);
	if (n->next)
		free_lst(n->next);
	free(n);
}

size_t get_lst(int fd, t_node *n)
{
	ssize_t	read_ret;
	size_t	bytes_read;

	bytes_read = 0;
	while (1) 
	{
		read_ret = read(fd, n->str, BUFFER_SIZE);
		if (read_ret == -1)
			return (0);
		if (index_in(n->str) >= 0)
			bytes_read += index_in(n->str);
		else
			bytes_read += read_ret;
		if (read_ret != BUFFER_SIZE || index_in(n->str) >= 0)
			break ;
		n->next = new_node();
		if (n->next == NULL)
			return (0);
		n = n->next;
	}
	return (bytes_read);
}

char	*join_lst(t_node *n, size_t content_len)
{
	char	*line;
	char	*ptr;

	line = malloc(sizeof(char) * (content_len + 1));
	if (line == NULL)
		return (NULL);
	line[content_len] = 0;
	ptr = line;
	while (n)
	{
		ptr = join(ptr, n->str);
		n = n->next;	
	}
	return (line);
}

char	*get_next_line(int fd)
{
	t_node		*head;
	char		*line;
	ssize_t		content_len;
	static size_t	already_read;

	if (BUFFER_SIZE == 0 || get_back(fd, already_read))
		return (NULL);
	head = new_node();
	content_len = get_lst(fd, head);
	line = NULL;
	if (content_len != 0)
		line = join_lst(head, content_len);
	already_read += content_len;
	free_lst(head);
	return (line);
}
