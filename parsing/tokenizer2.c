/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:39:20 by ibouram           #+#    #+#             */
/*   Updated: 2024/08/04 15:56:14 by ibouram          ###   ########.fr       */
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
	t_token	*current;

	tokenizer_1(splited, token);
	if (syntax_error(*token))
		return (1);
	tokenizer_2(token);
	replace_quotes(token);
	current = *token;
	while (current)
	{
		
		current->var_flg = 0;
		if (current->token && current->token[0] == '$')
			current->var_flg = 1;
		current = current->next;
	}
	expanding(*token, env);
	tokenizer_3(token);
	return (0);
}
