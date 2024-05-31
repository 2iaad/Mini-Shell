/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:10:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/31 11:00:27 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"
#include <stdio.h>
#include <sys/unistd.h>
#include <unistd.h>

void	cd_error(char *dir)
{
        write (2, "cd: ", 4);
        ft_putstr_fd (dir , 2);
        write (2, ": No such file or directory\n", 28);
}

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

void	update_pwd(t_env	*env) // update pwd and oldpwd variables after using cd
{
	char	*oldpwd;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
		{
			oldpwd = tmp->value;
			tmp->value = getcwd(NULL, -1337);
			if (!tmp->value)
				return (perror("getcwd"));
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "OLDPWD", 6))
		{
			free(tmp->value);
			tmp->value = oldpwd;
		}
		tmp = tmp->next;
	}
}

void    cd(t_list *lst)
{
	char	*dir;

	if (!lst->cmd[1]) // ila makanch second argument
		dir = home_path(lst->env); // kan9leb 3la HOME
	else
	 	dir = lst->cmd[1];

	if (!access(dir, F_OK))
	{
		if (chdir(dir) == -1)
			return (perror("chdir"));
		update_pwd(lst->env); // update the PWD and the OLDPWD in the env variables after dir change
	}
	else
	{
		if (!lst->cmd[1])
			write(2, "cd: HOME not set\n", 17);
		else
			cd_error(dir);
	}
}
