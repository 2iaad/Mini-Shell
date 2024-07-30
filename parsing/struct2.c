/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 03:35:58 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/30 03:58:19 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		files_len;

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
	files_len = count_len(node, IN_FILE) + count_len(node, OUT_FILE)
		+ count_len(node, AOUT_FILE) + count_len(node, DELIMITER);
	if (files_len > 0)
	{
		final->files = malloc(sizeof(t_file) * (files_len + 1));
		if (!final->files)
			return (NULL);
	}
	else
		final->files = NULL;
	return (final);
}
