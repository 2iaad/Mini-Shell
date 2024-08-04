/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:58:31 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 13:49:55 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_cmd(t_final *lst, int *fds, int flag)
{
	if (!lst->next)
		return ;
	if (flag == 0)
		if (pipe(fds) == -1)
			error("pipe", 1337);
	if (flag == 1)
	{
		close(fds[0]);
		if (dup2(fds[1], 1) == -1)
			error("dup2", 1337);
		close(fds[1]);
	}
	if (flag == 2)
	{
		close(fds[1]);
		if (dup2(fds[0], 0) == -1)
			error("dup2", 1337);
		close(fds[0]);
	}
}

void	child(t_final *lst, t_env **env, int *fds)
{
	int	r;

	file_opener(lst->files);
	if (lst->next && isatty(1))
		pipe_cmd(lst, &fds[0], 1);
	if (builtins(lst, env))
		return (r = exit_status(1, 0), exit(r));
	else
		execute_cmd(lst, *env);
}
