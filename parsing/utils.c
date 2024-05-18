/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:06:06 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/14 01:10:37 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while(s[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write (fd, s, ft_strlen(s));
}

int	whitespaces(char s)
{
	return (s == ' ' || s == '\t' || s == '\n' || s == '\v' || s == '\f' || s == '\r');
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dest;

	dest = (char *) malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int delimiters(char c)
{
	// evrinthing that is not a letter or a number and '_' is a delimiter
	return (!ft_isalnum(c) && c != '_');
}

int	ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
