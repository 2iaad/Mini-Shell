/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:49:39 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/12 02:27:58 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *line, int *i)
{
	if (!line[*i])
		return (0);
	if ((line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>'))
		{
			(*i)++;
			return (1);
		}
	if (line[*i] == '<' || line[*i] == '>')
		return (1);
	return (0);
}

void	skip_spaces(char *line, int *i, int inc)
{
	if (inc == 1)
		(*i)++;
	while (line[*i] && whitespaces(line[*i]))
		(*i)++;
}

int	syntax_error(char *line)
{
	int i;

	i = 0;
	skip_spaces(line, &i, 0);
	if (line[i] && line[i] == '|')
		return (printf("minishell: syntax error\n"), 1);
	while (line[i])
	{
		if (line[i] == '|')
		{
			skip_spaces(line, &i, 1);
			if (!line[i] || (line[i] && line[i] == '|'))
				return (printf("minishell: syntax error\n"), 1);
		}
		else if (is_operator(line, &i))
		{
			skip_spaces(line, &i, 1);
			if (!line[i] || is_operator(line, &i) || line[i] == '|')
				return (printf("minishell: syntax error\n"), 1);
		}
		else
			i++;
	}
	return (0);
}
