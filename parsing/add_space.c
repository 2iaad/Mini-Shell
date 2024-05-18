/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 05:57:38 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/14 02:22:15 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_len(char *line, int i)
{
	int len;

	len = ft_strlen(line);
	while (line[i])
	{
		if ((((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))) && valid_meta(line, i, 0, 1))
		{
			if (i > 1 && !whitespaces(line[i - 1]))
				len++;
			if (line[i + 2] && !whitespaces(line[i + 2]))
				len++;
			i++;
		}
		else if (((line[i] == '<' || line[i] == '>' || line[i] == '|')) && valid_meta(line, i, 0, 1))
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
	// cause check i - 1 so should i > 0
	if (i > 1 && !whitespaces(line[i - 1]))
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[i]; // add the char '>'
	new_line[(*j)++] = line[i]; // add the sec '>'
	if (line[i + 2] && !whitespaces(line[i + 2]))
		new_line[(*j)++] = ' ';
}

void	spaces_sing_quot(char *new_line, char *line, int *j, int i)
{
	// cause check i - 1 so should i > 0
	if (i > 0 && !whitespaces(line[i - 1]))
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[i]; // add the char '>'
	if (line[i + 1] && !whitespaces(line[i + 1]))
		new_line[(*j)++] = ' ';
}

int	trim_line_len(char *line)
{
	int len;
	int	i;
	int	j;

	len = 0;
	i = 0;
	j = ft_strlen(line) - 1;
	while (line[i] && whitespaces(line[i]))
		i++;
	if (i == ft_strlen(line))
		return (0);
	while (j > 0 && whitespaces(line[j]))
		j--;
	len = j - i + 1;
	return (len);
}
//          1234         

char	*trim_line(char *line)
{
	int	i;
	int	j;
	char	*new_line;
	int		len;

	len = trim_line_len(line);
	if (len == 0)
		return (NULL);
	(1) && (i = 0, j = 0, new_line = NULL);
	// printf("len: %d\n", len); to know how space to remove
	new_line = malloc(len + 1);
	if (!new_line)
		return (NULL);
	while (line[i] && whitespaces(line[i]))
		i++;
	while (line[i] && j < len)
	{
		new_line[j] = line[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*space(char *line, int i, int j)
{
	int len;
	char *new_line;

	len = space_len(line, 0);
	if (len == 0)
		return (NULL);
	new_line = malloc((len) + 1);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if ((((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))) && valid_meta(line, i, 0, 1))
		{
			spaces_doubl_quot(new_line, line, &j, i);
			i++;
		}
		else if (((line[i] == '<' || line[i] == '>' || line[i] == '|')) && valid_meta(line, i, 0, 1))
			spaces_sing_quot(new_line, line, &j, i);
		else
			new_line[j++] = line[i];
		i++;
	}
	if (!new_line)
		return (NULL);
	new_line[j] = '\0';
	return (new_line);
}
