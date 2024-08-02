/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:10:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/02 21:48:20 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*home_path(t_env	*env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "HOME", 4))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

bool	init_pwd(t_env ***env, char **oldpwd)
{
	t_env	*tmp;
	bool	flag;

	(1 == 1) && ((tmp = *(*env)) && (flag = false));
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
		{
			flag = true;
			*oldpwd = tmp->value;
			tmp->value = getcwd(NULL, -1337);
			if (!tmp->value)
				return (perror("getcwd"), exit_status(1, 1), true);
			add_to_gc(tmp->value);
		}
		tmp = tmp->next;
	}
	if (!flag)
	{
		char *value = getcwd(NULL, -1337);
		if (!value)
			return (perror("getcwd"), exit_status(1, 1), true);
		ft_lstadd_back(*env, ft_lstnew(ft_strdup("PWD"), value));
	}
	return (false);
}

bool	init_oldpwd(t_env	**env)
{
	bool	flag;
	t_env	*tmp;
	char	*oldpwd;

	(1 == 1) && ((tmp = *env) && (oldpwd = NULL) && (flag = false));
	if (init_pwd(&env, &oldpwd))
		return (true);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			flag = true;
		}
		tmp = tmp->next;
	}
	if (!flag)
		ft_lstadd_back(env, ft_lstnew(ft_strdup("OLDPWD"), ft_strdup(oldpwd)));
	return (false);
}

void	init_dir(char **final_cmd, t_env *env, char **dir)
{
	if (!final_cmd[1] || !final_cmd[1][0]
	|| !ft_strncmp(final_cmd[1], ".", 1)
	|| !ft_strncmp(final_cmd[1], "~", 1))
		*dir = home_path(env);
	else
		*dir = final_cmd[1];
}

void	cd(t_final *lst, t_env *env)
{
	char	*dir;

	if (!lst->final_cmd[1])
		dir = NULL;
	else if (lst->final_cmd[1] && !lst->final_cmd[1][0])
		return ;
	else if (lst->final_cmd[1][0] == '-' && lst->final_cmd[1][1] == '\0')
		return (pwd());
	init_dir(lst->final_cmd, env, &dir);
	if (!access(dir, F_OK))
	{
		if (chdir(dir) == -1)
			return ((void)exit_status(1, 1), perror("chdir"));
		if (!init_oldpwd(&env))
			exit_status(0, 1);
	}
	else
	{
		if (!lst->final_cmd[1])
			write(2, "cd: HOME not set\n", 17);
		else
			cd_error(dir);
		exit_status(1, 1);
	}
}
