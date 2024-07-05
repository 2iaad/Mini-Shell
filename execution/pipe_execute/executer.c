/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/05 08:58:29 by zderfouf         ###   ########.fr       */
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

void	init_secfds(int *sec_fd)
{
	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
	if (sec_fd[0] == -1 || sec_fd[1] == -1)
		error("dup", 1337);
}

void	multiple(t_final *lst, t_env *env, char **envp)
{
	int	pid;
	int exit_status;
	int	fds[2][2]; // fds[0] ---> fds[2] ###### fds[1] ----> sec_fd

	init_secfds(&fds[1][0]);
	while (lst)
	{
		pipe_cmd(lst, &fds[0][0], 0);
		pid = fork();
		if (pid == -1)
			error("fork", 1337);
		if (!pid)
			child(lst, env, fds[0], envp, fds[1][0]);
		else
		{
			pipe_cmd(lst, &fds[0][0], 2);
			lst = lst->next;
		}
	}
	multiple_helper(fds[1], exit_status);
}

void	single(t_final *lst, t_env *env, char **envp)
{
	int		pid;
	int		sec_fd;
	bool	flag;

	flag = false;
	sec_fd = dup(STDIN_FILENO);
	if (!flag)
	{
		pid = fork();
		if (!pid)
			child(lst, env, &pid, envp, sec_fd);
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
