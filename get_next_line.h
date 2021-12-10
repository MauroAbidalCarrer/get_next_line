/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:27:44 by maabidal          #+#    #+#             */
/*   Updated: 2021/12/10 16:30:14 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include<unistd.h>
#include<limits.h>
#include<stdlib.h>
#define BUFFER_SIZE 10
#define MAX_FD 10

char	*get_next_line(int fd);
char	*join(char *s1, char *s2);
size_t	ft_strlen(char *str);
char	*r_join(char *s1, char *s2, size_t len);
char	*new_str(size_t len);
size_t	n_index(char *str);
#endif
