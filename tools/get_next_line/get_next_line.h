/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:39:07 by zderfouf          #+#    #+#             */
/*   Updated: 2024/01/17 16:02:18 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337

# endif

size_t	gnl_ft_strlen(char *str);
char	*gnl_ft_strchr(char *str, int c);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*gnl_ft_strdup(char *s);

char	*preserve(char *left_str);
char	*get_next_line(int fd);
char	*read_line(int fd, char *str);
char	*new_line(char *str);

#endif
