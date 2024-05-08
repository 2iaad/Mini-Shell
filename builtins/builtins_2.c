/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/08 15:20:55 by zderfouf         ###   ########.fr       */
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
	// lst->env_args = NULL;
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
}

void	export_data(t_list *lst) // doesnt have to work if the key is a number or '=' , have to be ranged between 'a' and 'z'
{
	char	**str;
	t_env	*tmp;

	str = custumized_ft_split(lst->cmd[1], '='); // it segf if there is no "="
	if (!str)
		return ;
	ft_lstadd_back(&lst->env_args, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
	ft_free(str);
}

// void	unset_tool(t_env	*env_args)
// {
// 	t_env	*tmp;

// 	tmp = env_args;
// 	while (tmp)
// 	{
// 		if 
// 	}
// }

void	unset(t_list	*lst)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = lst->env_args;
	if (!lst->cmd[1])
		return ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, lst->cmd[1], ft_strlen(lst->cmd[1])))
		{
			printf("%s", tmp->key);
			tmp2 = tmp->next;
			free(tmp->key);
			free(tmp->value);
		}
		tmp = tmp->next;
	}
}