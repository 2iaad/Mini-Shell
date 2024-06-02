/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:58:31 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 19:07:10 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipex(char *cmd, char **env)
{
	int		pid;
	int		fds[2];

	if (pipe(fds) == -1)
		error("pipe", 0);
	pid = fork();
	if (pid == -1)
		error("fork", 0);
	else if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execute_cmd(cmd, env);
	}
	else
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
	}
}

int	normal_file_opener(int a, char *file)
{
	int	fd;

	fd = 0;
	if (a == 0)
	{
		fd = open(file, O_RDONLY, 0644);
		dup2(fd, 0);
		close(fd);
	}
	if (a == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, 1);
		close(fd);
	}
	if (fd == -1)
	{
		ft_putstr_fd("./pipex: no such file or directory: ", 2);
		ft_putendl_fd(file, 2);
		exit(1);
	}
	return (fd);
}

void	first_child(char **av, char **ev)
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
		error("pipe", 0);
	pid = fork();
	if (pid == -1)
		error("fork", 0);
	if (!pid)
	{
		normal_file_opener(0, av[1]);
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execute_cmd(av[2], ev);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
	}
}

void	last_child(char **av, char **ev, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error("pid", 0);
	if (!pid)
		execute_cmd(av[i], ev);
}

void	pipex_main(int ac, char **av, char **env)
{
	int		i;

	i = 3;
	look_for_paths(env);
	if (ac < 5)
		error("retry with this: ./pipex infile cmd cmd outfile", 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		heredoc_limiter(av, ac);
	else
	{
		first_child(av, env);
		normal_file_opener(1, av[ac - 1]);
	}
	while (i < ac - 2)
		pipex(av[i++], env);
	last_child(av, env, i);
	while (wait(NULL) != -1)
		i++;
}


int	main(int ac, char **av, char **env)
{
	pipex_main(ac, av, env);
}