/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equals_spliter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:53:30 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/12 10:55:21 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *first_word(const char *str, char c)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	s = malloc(sizeof(char) * (i - j) + 1);
	if (!s)
		return (NULL);
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}
char *second_word(const char *str, char c)
{
	int i;
	int j;
	char *s;

	j = 0;
	i = ft_strlen((char *)str);
	while (str[j] != c)
		j++;
	j++;
	s = malloc(sizeof(char) * (i - j) + 1);
	i = 0;
	while (str[j])
	{
		s[i] = str[j];
		j++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char **custumized_ft_split(const char *str, char c)
{
	char	**s;

	if (!ft_strchr(str, c))
	{
		s = (char **) malloc (sizeof(char *) * 2);
		if (!s)
			return (NULL);
		s[0] = first_word(str, '=');
		s[1] = NULL;
		return (s);
	}
	s = (char **) malloc (sizeof(char *) * 3);
	if (!s)
		return (NULL);
	s[0] = first_word(str, c);
	s[1] = second_word(str, c);
	s[2] = NULL;
	return (s);
}
