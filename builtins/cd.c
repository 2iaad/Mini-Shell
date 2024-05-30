/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:10:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/30 18:31:45 by zderfouf         ###   ########.fr       */
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
			perror("chdir");
	}
	else
	{
		if (!lst->cmd[1])
			write(2, "cd: HOME not set\n", 17);
		else
			cd_error(dir);
	}
}
