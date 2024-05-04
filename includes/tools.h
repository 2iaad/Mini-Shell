/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/04 16:50:21 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "minishell.h"

int     ft_strlen(char *str);
void    ft_free(char **str);
int     ft_strcmp(char *s1, char *s2, int len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int     flag_check(char *s1);
char	**ft_split(const char *s, char c);
void    ft_putstr(char *str);

#endif