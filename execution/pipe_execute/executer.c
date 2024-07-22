/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/22 00:14:30 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	init_exitstatus(t_env *env, int exit_status)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	exit_status = WEXITSTATUS(exit_status);
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->key, "?", 1))
// 		{
// 			free(tmp->value);
// 			tmp->value = ft_itoa(exit_status);
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	multiple(t_final *lst, t_env **env)
{
	pid_t	pid;
	int		exit_status;
	int		fds[2][2]; // fds[0] ---> fds[2] ###### fds[1] ----> sec_fd

	init_secfds(&fds[1][0]);
	while (lst)
	{
		pipe_cmd(lst, &fds[0][0], 0);
		// heredoc_opener(&lst->files, *env, fds[1][0]);
		pid = fork();
		if (pid == -1)
			error("fork", 1337);
		if (!pid)
			child(lst, env, fds[0], fds[1][0]);
		else
		{
			pipe_cmd(lst, &fds[0][0], 2);
			lst = lst->next;
		}
	}
	multiple_helper(&env ,fds[1], exit_status);
	init_exitstatus(env, 1337,exit_status);
}

void	single(t_final *lst, t_env **env)
{
	pid_t	pid;
	int		sec_fd[2];
	int		exit_status;

	init_secfds(sec_fd);
	heredoc_opener(&lst->files, *env, sec_fd[0]);
	if (!b_file_opener(lst->files))
		return ;
	if (!builtins(lst, env)) // ila makantch command builtin
	{
		pid = fork();
		if (!pid)
			execute_cmd(lst, *env);
		else
		{
			multiple_helper(&env, sec_fd, exit_status);
			init_exitstatus(env, 1337, exit_status);
		}
	}
}

void	execution(t_final *lst, t_env **env)
{
	parce_files(&lst);
	if (lst->next)
		multiple(lst, env);
	else
	 	single(lst, env);
	t_env *tmp = *env;
	printf("\n\n");
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "?", 1))
			printf("exit_status in the outside:%s\n", tmp->value);
		tmp = tmp->next;
	}
}