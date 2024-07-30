/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 00:40:47 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/29 05:49:56 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsiz)
{
	size_t	i;

	if (dstsiz == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsiz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsiz > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dstsize == 0 && !dst)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	i = 0;
	while (src[i] != '\0' && len_dst + i < dstsize - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

char	*ft_strjoin_parse(char *s1, char *s2)
{
	int		t_len;
	char	*s;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	t_len = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc (t_len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	ft_strlcpy(s, s1, t_len + 1);
	ft_strlcat(s, s2, t_len + 1);
	return (s);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *) malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
