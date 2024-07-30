/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:10 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/29 23:33:29 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	handle_meta(char *line, int *j, int i, int *valid)
{
	int		in1;
	int		in2;
	char	quote;

	in1 = *j;
	quote = line[(*j)++];
	while (line[*j] && line[*j] != quote)
		(*j)++;
	if (line[*j] == quote)
	{
		in2 = *j;
		(*j)++;
	}
	if (i > in1 && i < in2)
	{
		*valid = 0;
		return (1);
	}
	return (0);
}

int	vm2(char *line, int i, int j, int valid)
{
	int		in1;
	int		in2;
	char	quote;

	while (line[j])
	{
		if (line[j] == -2)
		{
			quote = line[j++];
			while (line[j] && line[j] != quote)
				j++;
			if (line[j])
				j++;
		}
		else if (line[j] == -1)
		{
			if (handle_meta(line, &j, i, &valid))
				break ;
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
