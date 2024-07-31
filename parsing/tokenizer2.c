/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:39:20 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/31 01:19:09 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_quotes(t_token **token)
{
	t_token	*node;
	int		i;

	node = *token;
	while (node)
	{
		i = 0;
		while (node->token[i])
		{
			if (node->token[i] == '\'')
				node->token[i] = -1;
			else if (node->token[i] == '\"')
				node->token[i] = -2;
			i++;
		}
		node = node->next;
	}
}

int	tokenizer(char **splited, t_token **token, t_env *env)
{
	int	ambg_redir;

	tokenizer_1(splited, token);
	if (syntax_error(*token))
		return (1);
	tokenizer_2(token);
	replace_quotes(token);
	ambg_redir = expanding(*token, env);
	if (ambg_redir)
	{
		exit_status(1, 1);
		return (0);
	}
	tokenizer_3(token);
	return (0);
}
