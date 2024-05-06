/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/06 18:04:27 by zderfouf         ###   ########.fr       */
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
	lst->env_args = NULL;
    while (lst->env[i])
    {
        str = ft_split(lst->env[i], '='); // i split with '=' and take the variable name
		ft_lstadd_back(&lst->env_args, ft_lstnew(ft_strdup(str[0]), ft_strdup(getenv(str[0])))); // strdup bec bla strdup makhdmatch ez
        ft_free(str);
        i++;
    }
	tmp = lst->env_args; // to keep the linked list preserved for later freeing of the linked list
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_lstclear(&lst->env_args);
}