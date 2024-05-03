/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/03 17:35:03 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "minishell.h"

int     ft_strlen(char *str);
int     ft_strcmp(char *s1, char *s2, int len);
int     flag_check(char *s1);
char	**ft_split(const char *s, char c);
void    ft_putstr(char *str);

#endif