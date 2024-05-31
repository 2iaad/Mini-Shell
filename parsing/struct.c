/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:30:14 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/31 23:46:12 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(t_token *node, int type)
{
	int	i;

	i = 0;
	while (node && node->type != PIPE)
	{
		if (node->type == type)
			i++;
		node = node->next;
	}
	return (i);
}

t_final	*init_final(t_token **nodee)
{
	t_final	*final;
	t_token	*node;

	node = *nodee;
	final = malloc(sizeof(t_final));
	if (!final)
		return (NULL);
	final->cmd = NULL;
	final->args = NULL;
	if (count_len(node, OPTION) > 0)
	{
		final->args = malloc(sizeof(char *) * (count_len(node, OPTION) + 1));
		if (!final->args)
			return (NULL);
		final->args[count_len(node, OPTION)] = NULL;
	}
	if (count_len(node, IN_FILE) > 0)
	{
		final->in_file = malloc(sizeof(char *) * (count_len(node, IN_FILE) + 1));
		if (!final->in_file)
			return (NULL);
		final->in_file[count_len(node, IN_FILE)] = NULL;
	}
	if (count_len(node, OUT_FILE) > 0)
	{
		final->out_file = malloc(sizeof(char *) * (count_len(node, OUT_FILE) + 1));
		if (!final->out_file)
			return (NULL);
		final->out_file[count_len(node, OUT_FILE)] = NULL;
	}
	if (count_len(node, AOUT_FILE) > 0)
	{
		final->aout_file = malloc(sizeof(char *) * (count_len(node, AOUT_FILE) + 1));
		if (!final->aout_file)
			return (NULL);
		final->aout_file[count_len(node, AOUT_FILE)] = NULL;
	}
	if (count_len(node, REDIR_HEREDOC) > 0)
	{
		final->heredoc = malloc(sizeof(char *) * (count_len(node, REDIR_HEREDOC) + 1));
		if (!final->heredoc)
			return (NULL);
		final->heredoc[count_len(node, REDIR_HEREDOC)] = NULL;
	}
	return (final);
}

t_final	*struct_init(t_token **token)
{
	t_token *node;
	t_final *final;
	int 	i;
	int		opt_index;
	int     in_index;
	int     out_index;
	int     aout_index;
	int     heredoc_index;

	(1) && (i = 0, opt_index = 0, in_index = 0, out_index = 0, aout_index = 0, heredoc_index = 0);
	node = *token;
	while (node)
	{
		if (node == *token || node->type == PIPE)
		{
			if (node->type == PIPE)
				node = node->next;
			final = init_final(&node);
			if (!final)
				return (NULL);
			while (node && node->type != PIPE)
			{
				if (node->type == CMD)
					final->cmd = ft_strdup(node->token);
				else if (node->type == OPTION)
					final->args[opt_index++] = ft_strdup(node->token);
				else if (node->type == IN_FILE)
					final->in_file[in_index++] = ft_strdup(node->token);
				else if (node->type == OUT_FILE)
					final->out_file[out_index++] = ft_strdup(node->token);
				else if (node->type == AOUT_FILE)
					final->aout_file[aout_index++] = ft_strdup(node->token);
				else if (node->type == REDIR_HEREDOC)
					final->heredoc[heredoc_index++] = ft_strdup(node->token);
				node = node->next;
			}
		}
		else
			node = node->next;
	}
	printf("cmd: %s\n", final->cmd);
	printf("args: %s\n", final->args[0]);
	printf("out_file: %s\n", final->out_file[0]);
	printf("in_file: %s\n", final->in_file[0]);
	printf("aout_file: %s\n", final->aout_file[0]);
	printf("heredoc: %s\n", final->heredoc[0]);
	return (final);
}
