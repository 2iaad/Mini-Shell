/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:10 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/30 22:50:29 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_meta(char *line, int i, int j, int valid)
{
	int		in1;
	int		in2;
	char	quote;

	while (line[j])
	{
		if (line[j] == '\'' || line[j] == '\"')
		{
			in1 = j;
			quote = line[j++];
			while (line[j] && line[j] != quote)
				j++;
			if (line[j] == quote)
				in2 = j;
			if (i > in1 && i < in2)
			{
				valid = 0;
				break ;
			}
		}
		else
			j++;
	}
	return (valid);
}

int	valid_meta2(char *line, int i, int j, int valid)
{
	int		in1;
	int		in2;
	char	quote;

	while (line[j])
	{
		if (line[j] == '\"')
		{
			quote = line[j++];
			while (line[j] && line[j] != quote)
				j++;
			j++;
		}
		else if (line[j] == '\'')
		{
			in1 = j;
			quote = line[j++];
			while (line[j] && line[j] != quote)
				j++;
			if (line[j] == quote)
			{
				in2 = j;
				j++; // to skip the quote
			}
			if (i > in1 && i < in2)
			{
				valid = 0;
				break ;
			}
		}
		else
			j++;
	}
	return (valid);
}


int	check_quotes(char *line)
{
	int	i;
	int	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}

int	quotes_len(char *line)
{
	int	i;
	int	len;
	char	quote;

	i = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			len--;
			i++;
			while (line[i] && line[i] != quote)
				i++;
			len--;
			i++;
		}
		else
			i++;
	}
	return (len);
}

char	*remove_quotes(char *line)
{
	int i = 0;
	int j = 0;
	int	len;
	char quote;
	char *new_line;

	len = quotes_len(line);
	if (len == 0)
		return (ft_strdup(""));
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				new_line[j++] = line[i++];
			i++;
		}
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
