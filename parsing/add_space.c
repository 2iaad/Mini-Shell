/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 05:57:38 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/09 05:42:37 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	space_len(char *line, int i, int j)
{
	int	len;

	len = ft_strlen(line);
	while (line[i])
	{
		if ((((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')))
			&& valid_meta(line ,i, 0, 1))
		{
			if (i > 1 && !whitespaces(line[i - 1]))
				len++;
			if (line[i + 2] && !whitespaces(line[i + 2]))
				len++;
			i++;
		}
		else if (((line[i] == '<' || line[i] == '>' || line[i] == '|' )) 
				&& valid_meta(line ,i, 0, 1))
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
	//cause check i - 1 so should i > 0
	if (i > 1 && !whitespaces(line[i - 1]))
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[i]; // add the char '>'
	new_line[(*j)++] = line[i]; // add the sec '>'
	if (line[i + 2] && !whitespaces(line[i + 2]))
		new_line[(*j)++] = ' ';
}

void	spaces_sing_quot(char *new_line, char *line, int *j, int i)
{
	//cause check i - 1 so should i > 0
	if (i > 0 && !whitespaces(line[i - 1]))
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[i]; // add the char '>'
	if (line[i + 1] && !whitespaces(line[i + 1]))
		new_line[(*j)++] = ' ';
}
char	*space(char *line, int i, int j)
{
	int 	len;
	char 	*new_line;

	len = space_len(line, 0, 0);
	new_line = malloc((len) + 1);
	while (line[i])
	{
		if ((((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')))
			&& valid_meta(line ,i, 0, 1))
		{
			spaces_doubl_quot(new_line, line, &j, i);
			i += 2;
		}
		else if (((line[i] == '<' || line[i] == '>' || line[i] == '|'))
				&& valid_meta(line ,i, 0, 1))
			spaces_sing_quot(new_line, line, &j, i);
		else
			new_line[j++] = line[i];
		i++;
	}
	malloc_faill(new_line);
	new_line[j] = '\0';
	return (new_line);
}
