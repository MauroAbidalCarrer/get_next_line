/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:27:44 by maabidal          #+#    #+#             */
/*   Updated: 2022/01/03 15:53:13 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include<unistd.h>
#include<limits.h>
#include<stdlib.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif
#ifndef MAX_FD
#define MAX_FD 1024
#endif
#ifndef MAX_BS
#define MAX_BS 8200000
#endif
char	*get_next_line(int fd);
char	*join(char *s1, char *s2);
size_t	ft_strlen(char *str);
char	*r_join(char *s1, char *s2, size_t len);
char	*alloc_line(size_t len);
size_t	n_index(char *str);
#endif
