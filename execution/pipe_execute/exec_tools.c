/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:26:17 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/01 16:00:11 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execve_error(int flag, char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == 0)
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit(2);
	}
	if (!flag)
		ft_putstr_fd("No such file or directory: ", 2);
	else
		ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(127);
}

char	*look_for_paths(char **ev)
{
	if (!*ev)
		return ("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	while (*ev)
	{
		if (ft_strnstr(*ev, "PATH=", ft_strlen(*ev)))
			return (*ev + ft_strlen("PATH="));
		ev++;
	}
	return (NULL);
}

char	*right_path(char **s_cmd, char **env)
{
	int		i;
	char	*l_path;
	char	**s_path;
	char	*tmp;
	char	*r_path;

	i = -1;
	l_path = look_for_paths(env);
	s_path = ft_split(l_path, ':');
	if (!s_path)
		return (NULL);
	while (s_path[++i])
	{
		tmp = ft_strjoin(s_path[i], "/");
		r_path = ft_strjoin(tmp, s_cmd[0]);
		free(tmp);
		if (access(r_path, X_OK | F_OK) == 0)
			return (ft_free(s_path), r_path);
		free (r_path);
	}
	return (ft_free(s_path), s_cmd[0]);
}

void	init_path(t_final *lst, char **env, char **path, int *flag)
{
	if (ft_strchr(lst->final_cmd[0], '/'))
		(1 == 1) && (*path = lst->final_cmd[0]) && (*flag = 0);
	else
	{
		*path = right_path(lst->final_cmd, env);
		if (!(*path))
			*flag = 0;
		else
			*flag = 1;
	}
}

void	permission_checker(char *cmd)
{
	if (access(cmd, F_OK) == 0
		&& access(cmd, X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
}

void	execute_cmd(t_final	*lst, t_env *envp)
{
	int		flag;
	char	*path;
	char	**env;

	if (!lst->final_cmd[0])
		exit(0);
	env_maker(envp, &env);
	permission_checker(lst->final_cmd[0]); // ila kan ./main.c
	if (access(lst->final_cmd[0], F_OK | X_OK) == 0)
		execve(lst->final_cmd[0], lst->final_cmd, env);
	init_path(lst, env, &path, &flag);
	if (execve(path, lst->final_cmd, env) == -1)
	{
		exit_status(127, 1);
		execve_error(flag, lst->final_cmd[0]);
	}
}
