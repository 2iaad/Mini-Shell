/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:26:17 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/24 05:02:13 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	return (error("No path has been found.\n", 1), NULL);
}

char	*right_path(char **s_cmd, char **env)
{
	int		i;
	char	**s_path;
	char	*tmp;
	char	*r_path;

	i = -1;
	s_path = ft_split(look_for_paths(env), ':');
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

void	env_maker(t_env *envp, char ***env)
{
	int		i;
	char	*str;
	t_env	*tmp;

	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	*env = (char **) malloc (sizeof(char *) * (i + 1));
	if (!*env)
		return ;
	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		(*env)[i] = ft_strjoin(str, tmp->value);
		free(str);
		tmp = tmp->next;
		i++;
	}
	(*env)[i] = NULL;
}

void	execve_error(int flag, char *cmd)
{
	if (!flag)
		ft_putstr_fd("No such file or directory: ", 2);
	else
		ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(127);
}

void	execute_cmd(t_final	*lst, t_env *envp)
{
	int		flag;
	char	*path;
	char	**env;

	env_maker(envp, &env);
	if (!lst->final_cmd[0]) // in the case "< $PWD"
		exit(0);
	if (access(lst->final_cmd[0], F_OK | X_OK) == 0)
		execve(lst->final_cmd[0], lst->final_cmd, env);
	if (ft_strchr(lst->final_cmd[0], '/')) // ila kant /ls || ./ls
	{
		flag = 0;
		path = lst->final_cmd[0];
	}
	else
	{
		flag = 1;
		path = right_path(lst->final_cmd, env);
	}
	if (execve(path, lst->final_cmd, env) == -1)
		execve_error(flag, lst->final_cmd[0]);
}
