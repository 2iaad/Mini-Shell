/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:30:14 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/04 10:59:00 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ls -la < lsls >> slsl -l | cat -e

void print_final(t_final *final) {
	t_final *tmp;
	tmp = final;
	while (tmp)
	{
		int i = 0;
		printf("--------------------\n");
		printf("Command: %s\n", tmp->cmd ? tmp->cmd : "NULL");
		printf("--------------------\n");

		printf("Options: ");
		if (tmp->args)
		{
			while (tmp->args[i] != NULL)
			{
					// printf("  %s\n", tmp->args[i]);
					puts(tmp->args[i]);
				// printf("  %s\n", tmp->args[i]);
				i++;
			}
			if (i == 0) {
				printf("  NULL\n");
			}
		} else {
			printf("  NULL\n");
		}

		printf("Input Files: ");
		if (tmp->in_file) {
			for (i = 0; tmp->in_file[i]; i++) {
				printf("  %s\n", tmp->in_file[i]);
			}
			if (i == 0) {
				printf("  NULL\n");
			}
		} else {
			printf("  NULL\n");
		}

		printf("Output Files: ");
		if (tmp->out_file) {
			for (i = 0; tmp->out_file[i]; i++) {
				printf("  %s\n", tmp->out_file[i]);
			}
			if (i == 0) {
				printf("  NULL\n");
			}
		} else {
			printf("  NULL\n");
		}

		printf("Append Output Files: ");
		if (tmp->aout_file) {
			for (i = 0; tmp->aout_file[i]; i++) {
				printf("  %s\n", tmp->aout_file[i]);
			}
			if (i == 0) {
				printf("  NULL\n");
			}
		} else {
			printf("  NULL\n");
		}

		printf("Delimiter: ");
		if (tmp->heredoc) {
			for (i = 0; tmp->heredoc[i]; i++) {
				printf("  %s\n", tmp->heredoc[i]);
			}
			if (i == 0) {
				printf("  NULL\n");
			}
		} else {
			printf("  NULL\n");
		}
		printf("*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*\n");
		tmp = tmp->next;
	}
}

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
	if (count_len(node, OPTION) > 0)
	{
		final->args = malloc(sizeof(char *) * (count_len(node, OPTION) + 1));
		if (!final->args)
			return (NULL);
		final->args[count_len(node, OPTION)] = NULL;
	}
	else
		final->args = NULL;
	if (count_len(node, IN_FILE) > 0)
	{
		final->in_file = malloc(sizeof(char *) * (count_len(node, IN_FILE) + 1));
		if (!final->in_file)
			return (NULL);
		final->in_file[count_len(node, IN_FILE)] = NULL;
	}
	else
		final->in_file = NULL;
	if (count_len(node, OUT_FILE) > 0)
	{
		final->out_file = malloc(sizeof(char *) * (count_len(node, OUT_FILE) + 1));
		if (!final->out_file)
			return (NULL);
		final->out_file[count_len(node, OUT_FILE)] = NULL;
	}
	else
		final->out_file = NULL;
	if (count_len(node, AOUT_FILE) > 0)
	{
		final->aout_file = malloc(sizeof(char *) * (count_len(node, AOUT_FILE) + 1));
		if (!final->aout_file)
			return (NULL);
		final->aout_file[count_len(node, AOUT_FILE)] = NULL;
	}
	else
		final->aout_file = NULL;
	if (count_len(node, REDIR_HEREDOC) > 0)
	{
		final->heredoc = malloc(sizeof(char *) * (count_len(node, DELIMITER) + 1));
		if (!final->heredoc)
			return (NULL);
		final->heredoc[count_len(node, DELIMITER)] = NULL;
	}
	else
		final->heredoc = NULL;
	return (final);
}


t_final	*struct_init(t_token **token)
{
	t_token *node;
	t_final *final;
	t_final *tmp;
	int		opt_index;
	int     in_index;
	int     out_index;
	int     aout_index;
	int     heredoc_index;

	node = *token;
	final = NULL;
	while (node)
	{
		if (node == *token || node->type == PIPE)
		{
			(1) && (opt_index = 0, in_index = 0, out_index = 0, aout_index = 0, heredoc_index = 0);
			if (node->type == PIPE)
				node = node->next;
			tmp = init_final(&node);
			if (!tmp)
				return (NULL);
			while (node && node->type != PIPE)
			{
				if (node->type == CMD)
					tmp->cmd = ft_strdup(node->token);
				else if (node->type == OPTION)
				{
					tmp->args[opt_index++] = ft_strdup(node->token);
				}
				else if (node->type == IN_FILE)
					tmp->in_file[in_index++] = ft_strdup(node->token);
				else if (node->type == OUT_FILE)
					tmp->out_file[out_index++] = ft_strdup(node->token);
				else if (node->type == AOUT_FILE)
					tmp->aout_file[aout_index++] = ft_strdup(node->token);
				else if (node->type == DELIMITER)
					tmp->heredoc[heredoc_index++] = ft_strdup(node->token);
				node = node->next;
			}
			tmp->next = NULL;
			ft_lstadd_back3_parse(&final, tmp);
		}
		else
			node = node->next;
	}
	print_final(final);
	return (final);
}
