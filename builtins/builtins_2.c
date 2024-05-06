/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/06 16:09:01 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// do the expanding
// each string expanded will get added to the cmd->env list
// check if there is $VAR and replace VAR with its value

void    env(t_list *lst) // didnt handle "no envirement" case!!
{
    int		i;
	char	**str;
	t_env	*tmp;
    
    i = 0;
    while (lst->env[i])
    {
        str = ft_split(lst->env[i], '='); // i split with '=' and take the variable name
		ft_lstadd_back(&lst->env_args, ft_lstnew(ft_strdup(str[0]), ft_strdup(getenv(str[0])))); // strdup bec bla strdup makhdmatch ez
        ft_free(str);
        i++;
    }
	// while (lst->env_args)
	// {
		
	// 	printf("%s--->", lst->env_args->key);
	// 	printf("%s\n", lst->env_args->value);
		
	// 	lst->env_args = lst->env_args->next;
	// }
	// ft_lstclear(&lst->env_args);
}