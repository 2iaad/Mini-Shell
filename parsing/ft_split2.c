/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:49:29 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/31 00:25:46 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_word(char *line, int *i)
{
	int		count;
	char	quote;

	count = 0;
	while (line[*i] && !whitespaces(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	return (count);
}

static int	count_words(char *line)
{
	int		i;
	int		count;
	char	quote;

	(1) && (i = 0, count = 0);
	while (line[i])
	{
		while (line[i] && whitespaces(line[i]))
			i++;
		if (line[i])
		{
			count++;
			count += process_word(line, &i);
		}
		i++;
		if (i > ft_strlen(line))
			break ;
	}
	return (count);
}

static int	calc_len(char *line)
{
	int		i;
	int		count;
	char	quote;

	(1) && (i = 0, count = 0);
	while (line[i] && !whitespaces(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			count++;
			while (line[i] && line[i] != quote)
				count += (++i, 1);
			if (line[i])
				count += (++i, 1);
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static char	*get_tok(char **line)
{
	int		i;
	char	*subs;
	int		len;

	subs = NULL;
	while (**line && whitespaces(**line))
		(*line)++;
	len = calc_len(*line);
	if (len == 0)
		return (NULL);
	subs = gv_coll(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = **line;
		i++;
		(*line)++;
	}
	subs[i] = '\0';
	return (subs);
}

char	**split_line(char *line)
{
	int		nbr_toks;
	char	**toks;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	nbr_toks = count_words(line);
	if (nbr_toks == 0)
		return (NULL);
	toks = gv_coll (sizeof(char *) * (nbr_toks + 1));
	if (!toks)
		return (NULL);
	while (i < nbr_toks)
	{
		toks[i] = get_tok(&line);
		if (!toks[i])
			return (NULL);
		i++;
	}
	toks[i] = NULL;
	i = 0;
	return (toks);
}
