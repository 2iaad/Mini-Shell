/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/30 05:48:32 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple_helper(int *sec_fd, int exit_status)
{
	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
		error("dup2", 1337);
	while (wait(&exit_status) != -1)
		;
	return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
}

void	multiple(t_final *lst, t_env *env, char **envp)
{
	int	pid;
	int exit_status;
	int	fds[2];
	int	sec_fd[2];

	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
	if (sec_fd[0] == -1 || sec_fd[1] == -1)
		error("dup", 1337);
	while (lst)
	{
		pipe_cmd(lst, &fds[0], 0);
		pid = fork();
		if (pid == -1)
			error("fork", 1337);
		if (!pid)
			child(lst, env, fds, envp);
		else
		{
			pipe_cmd(lst, &fds[0], 2);
			lst = lst->next;
		}
	}
	multiple_helper(sec_fd, exit_status);
}

void	single(t_final *lst, t_env *env, char **envp)
{
	int		pid;
	bool	flag;

	flag = false;
	builtins(lst, env, &flag);
	if (!flag)
	{
		pid = fork();
		if (!pid)
			child(lst, env, &pid, envp);
		else
		 	wait(NULL);
	}
}

void    execution(t_final *lst, t_env *env, char **envp)
{
	if (lst->next)
		multiple(lst, env, envp);
	else
	 	single(lst, env, envp);
}
