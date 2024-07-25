/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenzier2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:39:20 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/24 18:39:33 by ibouram          ###   ########.fr       */
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

void	tokenizer(char **splited, t_token **token, t_env *env)
{
	int	ambg_redir;

	tokenizer_1(splited, token);
	tokenizer_2(token);
	replace_quotes(token);
	ambg_redir = expanding(*token, env);
	if (ambg_redir)
	{
		init_exitstatus(&env, 1, 0);
		return ;
	}
	tokenizer_3(token);
}
