/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:29:47 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/06 23:22:34 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

t_node	*new_node()
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (n != NULL)
	{
		n->str = NULL;
		n->next = NULL;
	}
	return (n);
}

int	index_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*join(char *s1, char *s2)
{
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = *s2++;
	*s1 = 0;
	return s1;
}
