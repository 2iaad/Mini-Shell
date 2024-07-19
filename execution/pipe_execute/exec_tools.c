/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:26:17 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/19 09:56:31 by zderfouf         ###   ########.fr       */
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
	char	*str[2];
	t_env	*tmp;

	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	*env = (char **) malloc (sizeof(char *) * (i + 1));
	if (!*env)
		return ;
	tmp = envp;
	i = 0;
	while (tmp)
	{
		str[0] = ft_strdup(tmp->key);
		str[1] = ft_strjoin(str[0], "=");
		(*env)[i] = ft_strjoin(str[1], tmp->value);
		free(str[0]);
		free(str[1]);
		tmp = tmp->next;
		i++;
	}
	(*env)[i] = NULL;
}

void	execute_cmd(t_final	*lst, t_env *envp)
{
	char	*path;
	char	**env;

	env_maker(envp, &env);
	if (!lst->final_cmd[0]) // in the case "< $PWD"
		exit(0);
	if (access(lst->final_cmd[0], F_OK | X_OK) == 0)
		execve(lst->final_cmd[0], lst->final_cmd, env);
	path = right_path(lst->final_cmd, env);
	if (execve(path, lst->final_cmd, env) == -1)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(lst->final_cmd[0], 2);
		exit(1);
	}
}