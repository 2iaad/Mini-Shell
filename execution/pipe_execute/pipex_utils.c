/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/04 16:19:05 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error(char *str, int a)
{
	if (a == 1)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	exit(1);
}

char	*look_for_paths(char **ev)
{
	while (*ev)
	{
		if (ft_strnstr(*ev, "PATH=", ft_strlen(*ev)))
			return (*ev + ft_strlen("PATH="));
		ev++;
	}
	return (error("No path has been found.\n", 1), NULL);
}

char	*right_path(char *cmd, char **env)
{
	int		i;
	char	**s_path;
	char	**s_cmd;
	char	*tmp;
	char	*r_path;

	i = -1;
	s_cmd = ft_split(cmd, ' ');
	s_path = ft_split(look_for_paths(env), ':');
	while (s_path[++i])
	{
		tmp = ft_strjoin(s_path[i], "/");
		r_path = ft_strjoin(tmp, s_cmd[0]);
		free(tmp);
		if (access(r_path, X_OK | F_OK) == 0)
			return (ft_free(s_cmd), ft_free(s_path), r_path);
		free (r_path);
	}
	return (ft_free(s_cmd), ft_free(s_path), s_cmd[0]);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (access(s_cmd[0], F_OK | X_OK) == 0)
		execve(s_cmd[0], s_cmd, envp);
	path = right_path(cmd, envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free(s_cmd);
		exit(1);
	}
}
