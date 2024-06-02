/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:04:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/01 22:06:33 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_len(char *line)
{
	int		i;
	int		len;
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
	new_line = malloc(len + 1);
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
