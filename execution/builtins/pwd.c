/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:09:40 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/22 02:14:52 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    pwd(t_env *env)
{
    char *c_path;

    c_path = getcwd(NULL, -1337); // when giving NULL , the fun ignores the number of bytes of the array that have been given
    if (!c_path) // contains the path, that have been allocated by getcwd
	{
        perror("getcwd"); // return 
		return ;
	}
    printf("%s\n", c_path);
    free(c_path);
	init_exitstatus(&env, EXIT_SUCCESS, 0);
}

bool	env_checker(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void    env(t_final	*lst, t_env *env_list) // didnt handle "no envirement" case!!
{
	t_env *tmp;
	(void)lst;
	tmp = env_list; // to keep the linked list preserved for later freeing of the linked list
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "?", 1))
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value); // so i can print only variables that has a value(like bash)
		tmp = tmp->next;
	}
	init_exitstatus(&env_list, EXIT_SUCCESS, 0);
}
