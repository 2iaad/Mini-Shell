/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:10 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/30 22:01:02 by ibouram          ###   ########.fr       */
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

char	*remove_quotes(char *line)
{
	int i = 0;
	int j = 0;
	char *new_line;

	new_line = malloc(ft_strlen(line) + 1);
	if (!new_line)
		return NULL;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && valid_meta(line, i, 0, 1))
		{
			i++;
			continue;
		}
		new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
