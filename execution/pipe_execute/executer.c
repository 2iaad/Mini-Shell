/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 13:45:33 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	signal_checker(void)
{
	if (g_signal == 2)
	{
		exit_status(1, 1);
		return (true);
	}
	return (false);
}

void	multiple(t_final *lst, t_env **env)
{
	int		fds[2][2];

	init_secfds(&fds[1][0], 0);
	while (lst)
	{
		pipe_cmd(lst, &fds[0][0], 0);
		heredoc_opener(&lst->files, *env, fds[1][0]);
		if (signal_checker())
		{
			close(fds[0][0]);
			close(fds[0][1]);
			break ;
		}
		lst->pid = fork();
		if (lst->pid == -1)
			error("fork", 1337);
		if (!lst->pid)
			child(lst, env, fds[0]);
		else
			(1) && close (0), ft_help(fds, &lst, env);
	}
	(1) && (sig_check(), init_secfds(&fds[1][0], 1), 0);
}

void	single(t_final *lst, t_env **env)
{
	int		sec_fd[2];

	init_secfds(sec_fd, 0);
	heredoc_opener(&lst->files, *env, sec_fd[0]);
	if (signal_checker())
		return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
	if (!s_file_opener(lst->files))
		return ((void) exit_status(1, 1), init_secfds(sec_fd, 1));
	if (!builtins(lst, env))
	{
		lst->pid = fork();
		if (!lst->pid)
			execute_cmd(lst, *env);
		else
		{
			sig_check();
			waiter(lst, env);
		}
	}
	init_secfds(sec_fd, 1);
}

void	execution(t_final *lst, t_env **env, struct termios *p)
{
	if (g_signal == 2)
		g_signal = 0;
	parce_files(&lst);
	if (lst->next)
		multiple(lst, env);
	else
	{
		single(lst, env);
		tcsetattr(0, 0, p);
	}
}

void	error(char *str, int a)
{
	if (a == 1)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	exit(1);
}
