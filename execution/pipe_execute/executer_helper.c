/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:32:12 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/19 10:26:40 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	multiple_helper(int *sec_fd, int exit_status)
// {
// 	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
// 		error("dup2", 1337);
// 	while (wait(&exit_status) != -1)
// 		;
// 	return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
// }

// void	init_secfds(int *sec_fd)
// {
// 	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
// 	if (sec_fd[0] == -1 || sec_fd[1] == -1)
// 		error("dup", 1337);
// }

// void	single_redirect(t_final *lst, t_env *env)
// {
// 	if (lst->heredoc)
// 		heredoc_opener(lst->heredoc, env, 1337);
// 	if (lst->in_file)
// 		infile_opener(lst->in_file);
// 	if (lst->out_file)
// 		outfile_opener(lst->out_file);
// 	if (lst->aout_file)
// 		aoutfile_opener(lst->aout_file);
// }
