/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/06 15:46:27 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple(t_final *lst, t_env *env, char **envp)
{
	pid_t	pid;
	int		exit_status;
	int		fds[2][2]; // fds[0] ---> fds[2] ###### fds[1] ----> sec_fd

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
	pid_t	pid;
	bool	flag;
	int		sec_fd[2];

	sec_fd[0] = dup(0);
	sec_fd[1] = dup(1);
	flag = false;
	single_redirect(lst, env);
	builtins(lst, env, &flag);
	if (!flag) // ila makantch command builtin
	{
		pid = fork();
		if (!pid)
			execute_cmd(lst, envp);
		else
		 	wait(NULL);
	}
	dup2(sec_fd[0], 0);
	dup2(sec_fd[1], 1);
	
}

void    execution(t_final *lst, t_env *env, char **envp)
{
	if (lst->next)
		multiple(lst, env, envp);
	else
	 	single(lst, env, envp);
}
