/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/26 11:43:56 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple(t_final *lst, t_env **env)
{
	pid_t	pid;
	int		fds[2][2]; // fds[0] ---> fds[2] ###### fds[1] ----> sec_fd

	init_secfds(&fds[1][0], 0);
	while (lst)
	{
		pipe_cmd(lst, &fds[0][0], 0);
		heredoc_opener(&lst->files, *env, fds[1][0]);
		if (g_signal == 2)
			break ;
		pid = fork();
		if (pid == -1)
			error("fork", 1337);
		if (!pid)
			child(lst, env, fds[0]);
		else
		{
			close(0);
			pipe_cmd(lst, &fds[0][0], 2);
			lst = lst->next;
		}
	}
	multiple_helper(env);
	init_secfds(&fds[1][0], 1);
}

void	single(t_final *lst, t_env **env)
{
	pid_t	pid;
	int		sec_fd[2];

	init_secfds(sec_fd, 0);
	heredoc_opener(&lst->files, *env, sec_fd[0]);
	if (g_signal == 2)
		return ;
	s_file_opener(lst->files);
	if (!builtins(lst, env)) // ila makantch command builtin
	{
		pid = fork();
		if (!pid)
			execute_cmd(lst, *env);
		else
			multiple_helper(env);
	}
	init_secfds(sec_fd, 1);
}

void	execution(t_final *lst, t_env **env)
{
	parce_files(&lst);
	if (lst->next)
		multiple(lst, env);
	else
	 	single(lst, env);
	if (g_signal == 2)
		init_exitstatus(env, 1, 0);
	t_env *tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "?", 1))
			printf("exit status:%s\n", tmp->value);
		tmp = tmp->next;
	}
}
