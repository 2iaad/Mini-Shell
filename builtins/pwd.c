/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:09:40 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/15 10:13:43 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    pwd(void)
{
    char *c_path;

    c_path = getcwd(NULL, -1337); // when giving NULL , the fun ignores the number of bytes of the array that have been given
    if (!c_path) // contains the path, that have been allocated by getcwd
        perror("getcwd"); // return 
    printf("%s", c_path);
    free(c_path);
}

void    env(t_list *lst) // didnt handle "no envirement" case!!
{
	t_env *tmp;

	tmp = lst->env; // to keep the linked list preserved for later freeing of the linked list
	while (tmp)
	{
		printf("%s------>%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}