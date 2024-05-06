/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:48:54 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/06 15:48:13 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len == 0 && haystack == NULL)
		return (NULL);
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (needle[j] == haystack[i])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = (char *) malloc (sizeof(char) * ft_strlen(s1) + 1);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}