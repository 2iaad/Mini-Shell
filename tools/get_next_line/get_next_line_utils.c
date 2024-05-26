/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:36:11 by zderfouf          #+#    #+#             */
/*   Updated: 2024/01/17 15:35:13 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while ((str) && str[i])
		i++;
	return (i);
}

char	*gnl_ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*gnl_ft_strjoin(char *str, char *tempo)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	j = -1;
	s = (char *) malloc (gnl_ft_strlen(str) + gnl_ft_strlen(tempo) + 1);
	if (!s)
		return (free(str), str = NULL, NULL);
	while (str[++i])
		s[i] = str[i];
	while (tempo[++j])
		s[i + j] = tempo[j];
	s[i + j] = '\0';
	return (free(str), str = NULL, s);
}

char	*gnl_ft_strdup(char *src)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (gnl_ft_strlen(src) + 1));
	if (!str)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
