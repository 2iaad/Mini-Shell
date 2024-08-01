/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:09:40 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/01 09:31:31 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(void)
{
	char	*c_path;

	c_path = getcwd(NULL, -1337);
	if (!c_path)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", c_path);
	free(c_path);
	exit_status(0, 1);
}

bool	env_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
		{
			if (tmp->hidden == true) // in case env -i ---> env : PATH should be hidden
			{
				tmp = tmp->next;
				continue;
			}
			printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
	exit_status(0, 1);
}
