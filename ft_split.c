/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:35:47 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/04 17:49:56 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_s(char c, char *sub_s)
{
	int	i;

	i = 0;
	while (sub_s[i])
	{
		if (sub_s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	**free_memory(char **result, int sub)
{
	while (sub > 0)
	{
		sub--;
		free(result[sub]);
	}
	free(result);
	return (0);
}

static int	count_subs(const char *s, char *sub_s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (!is_in_s(s[i], sub_s))
		{
			count++;
			while (s[i] && !is_in_s(s[i], sub_s))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*copy_sub(char *dst, const char *src, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
		dst[i++] = src[start++];
	dst[i] = '\0';
	return (dst);
}

static char	**sub_process(const char *s, char *sub_s, char **res, int n)
{
	const char	*word_start;
	const char	*word_end;
	int			word;
	int			length;

	word = 0;
	while (word < n)
	{
		while (*s && is_in_s(*s, sub_s))
			s++;
		word_start = s;
		while (*s && !is_in_s(*s, sub_s))
			s++;
		word_end = s;
		length = word_end - word_start;
		res[word] = (char *)malloc(length + 1);
		if (!res[word])
			return (free_memory(res, word));
		copy_sub(res[word], word_start, 0, length);
		word++;
	}
	res[word] = NULL;
	return (res);
}

char	**ft_split(const char *s, char *sub_s)
{
	char			**res;
	unsigned int	num;

	if (!s)
		return (NULL);
	num = count_subs(s, sub_s);
	res = (char **)malloc((num + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = sub_process(s, sub_s, res, num);
	return (res);
}
