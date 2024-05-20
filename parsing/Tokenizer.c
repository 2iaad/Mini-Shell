/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 06:33:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/20 10:02:19 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_get_token(char *content, int type)
{
	t_token	*n;

	n = (t_token *)malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	n->token = ft_strdup(content);
	n->type = type;
	n->next = NULL;
	return (n);
}

int	is_oper(char *tok, int asc, int len)
{
	int	i;

	i = 0;
	if (ft_strlen(tok) == len)
	{
		while (i < len)
		{
			if (tok[i] != asc)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	tokenizer(char **splited, t_token **token)
{
	int	i;
	t_token *node;

	node = NULL;
	(void)token;
	i = 0;
	if (!splited)
		return ;
	while (splited[i])
	{
		if (is_oper(splited[i], -5, 1))
			node = ft_get_token("|", PIPE);
		else if (is_oper(splited[i], -1, 1))
			node = ft_get_token("<", REDIR_IN);
		else if (is_oper(splited[i], -3, 1))
			node = ft_get_token(">", REDIR_OUT);
		else if (is_oper(splited[i], -4, 2))
			node = ft_get_token(">>", REDIR_APPEND);
		else if (is_oper(splited[i], -2, 2))
			node = ft_get_token("<<", REDIR_HEREDOC);
		else
			node = ft_get_token(splited[i], WORD);
		if (node != NULL && node->token != NULL)
			ft_lstadd_back(token, node);
		i++;
	}
}
