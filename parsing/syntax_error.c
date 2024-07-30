/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:49:39 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/29 06:15:30 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_token *token)
{
	t_token	*node;

	node = token;
	if (node && node->type == PIPE)
		return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
	while (node)
	{
		if (node->type == PIPE)
		{
			if (!node->next || node->next->type == PIPE)
				return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
		}
		else if (node->type == REDIR_IN || node->type == REDIR_OUT
			|| node->type == REDIR_APPEND || node->type == REDIR_HEREDOC)
		{
			if (!node->next || node->next->type == PIPE
				|| node->next->type == REDIR_IN || node->next->type == REDIR_OUT
				|| node->next->type == REDIR_APPEND
				|| node->next->type == REDIR_HEREDOC)
				return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
		}
		node = node->next;
	}
	return (0);
}
