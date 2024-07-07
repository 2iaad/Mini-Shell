/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:55:06 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/07 16:51:26 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_l_files(char **l_in, char **l_out, char **l_aout,
					char **l_heredoc, t_file *files)
{
	t_file	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == IN_FILE)
			*l_in = tmp->file;
		else if (tmp->type == OUT_FILE)
			*l_out = tmp->file;
		else if (tmp->type == AOUT_FILE)
			*l_aout = tmp->file;
		else if (tmp->type == DELIMITER)
			*l_heredoc = tmp->file;
		tmp = tmp->next;
	}
}

void	parce_files(t_file **files)
{
	t_file	*tmp;
	char	*l_in;
	char	*l_out;
	char	*l_aout;
	char	*l_heredoc;

	tmp = *files;
	init_l_files(&l_in, &l_out, &l_aout, &l_heredoc, *files);
	while (tmp)
	{
		if (tmp->type == IN_FILE && tmp->file == l_in)
			tmp->last = true;
		else if (tmp->type == OUT_FILE && tmp->file == l_out)
			tmp->last = true;
		else if (tmp->type == AOUT_FILE && tmp->file == l_aout)
			tmp->last = true;
		else if (tmp->type == DELIMITER && tmp->file == l_heredoc)
			tmp->last = true;
		else
			tmp->last = false;
		tmp = tmp->next;
	}
}

void	redirector(t_final	*lst, t_env	*env)
{
	// while (lst->files)
	// {
	// 	if (lst->files->type == IN_FILE)
	// 		infile_opener(files->file);
		// if (lst->files->type == OUT_FILE)
		// 	outfile_opener(files);
		// if (lst->files->type == AOUT_FILE)
		// 	aoutfile_opener(files);
		// if (lst->files->type == DELIMITER)
		// 	heredoc_opener(lst, env);
	// }
}