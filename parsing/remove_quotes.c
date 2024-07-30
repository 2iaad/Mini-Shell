/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:04:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/30 04:51:56 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_len(char *line, int i)
{
	int		len;
	char	quote;

	if (!line)
		return (-1);
	len = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == -1 || line[i] == -2)
		{
			quote = line[i];
			len--;
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (len);
			len--;
			i++;
		}
		else
			i++;
	}
	return (len);
}

void	handle_quotes(char *line, char *new_line, int *i, int *j)
{
	char	quote;

	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
		new_line[(*j)++] = line[(*i)++];
	if (!line[*i])
		return ;
	(*i)++;
}

char	*remove_quotes(char *line)
{
	int		i;
	int		j;
	int		len;
	char	quote;
	char	*new_line;

	(1) && (i = 0, j = 0, len = quotes_len(line, i));
	if (len == -1)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	new_line = malloc(len + 1);
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == -1 || line[i] == -2)
			handle_quotes(line, new_line, &i, &j);
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}

void	token_quotes(t_token **token)
{
	t_token	*tmp;
	char	*tmp_token;

	tmp = *token;
	while (tmp)
	{
		tmp_token = tmp->token;
		tmp->token = remove_quotes(tmp->token);
		free(tmp_token);
		tmp = tmp->next;
	}
}
