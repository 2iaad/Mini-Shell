/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/06 15:48:04 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "minishell.h"

void    ft_putstr(char *str);
int     ft_strlen(char *str);
void    ft_free(char **str);
int     flag_check(char *s1);
char	*ft_strdup(char *s1);
char	**ft_split(const char *s, char c);
int     ft_strcmp(char *s1, char *s2, int len);
char	*ft_strnstr(const char *haystack, const char *needle, int len);


#endif