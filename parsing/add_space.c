/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 05:57:38 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/13 12:42:55 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_condition(char *line, int i)
{
	return (((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')));
}

int	space_len(char *line, int i)
{
	int	len;

	len = ft_strlen(line);
	while (line[i])
	{
		if (quotes_condition(line, i) && valid_meta(line, i, 0, 1))
		{
			if (i > 1 && !whitespaces(line[i - 1]))
				len++;
			if (line[i + 2] && !whitespaces(line[i + 2]))
				len++;
			i++;
		}
		else if (((line[i] == '<' || line[i] == '>' || line[i] == '|'))
			&& valid_meta(line, i, 0, 1))
		{
			if (i > 0 && !whitespaces(line[i - 1]))
				len++;
			if (line[i + 1] && !whitespaces(line[i + 1]))
				len++;
		}
		i++;
	}
	return (len);
}

void	spaces_doubl_quot(char *new_line, char *line, int *j, int i)
{
	if (i > 1 && !whitespaces(line[i - 1]))
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[i];
	new_line[(*j)++] = line[i];
	if (line[i + 2] && !whitespaces(line[i + 2]))
		new_line[(*j)++] = ' ';
}

void	spaces_sing_quot(char *new_line, char *line, int *j, int i)
{
	if (i > 0 && !whitespaces(line[i - 1]))
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[i];
	if (line[i + 1] && !whitespaces(line[i + 1]))
		new_line[(*j)++] = ' ';
}

char	*space(char *line, int i, int j)
{
	int		len;
	char	*new_line;

	len = space_len(line, 0);
	if (!len)
		return (NULL);
	new_line = malloc((len) + 1);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (quotes_condition(line, i) && valid_meta(line, i, 0, 1))
		{
			spaces_doubl_quot(new_line, line, &j, i);
			i++;
		}
		else if (((line[i] == '<' || line[i] == '>' || line[i] == '|'))
			&& valid_meta(line, i, 0, 1))
			spaces_sing_quot(new_line, line, &j, i);
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
