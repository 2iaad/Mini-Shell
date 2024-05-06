/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:10 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/06 19:03:59 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	space(char *line)
{
	// add space before and after "<", ">", ">>", "|"
	int	i;
	int len;

	i = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			//cause check i - 1 so should i > 0
			if (i > 0 && !whitespaces(line[i - 1]))
			{
				while (len > i)
				{
					line[len] = line[len - 1];
					len--;
				}
				line[i++] = ' ';
				len++;
			}
		}
		i++;
	}
}
