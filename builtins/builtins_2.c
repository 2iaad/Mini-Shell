/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/11 15:19:12 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

// do the expanding
// each string expanded will get added to the cmd->env list
// check if there is $VAR and replace VAR with its value

void    env(t_list *lst) // didnt handle "no envirement" case!!
{
	t_env *tmp;

	tmp = lst->env_args; // to keep the linked list preserved for later freeing of the linked list
	while (tmp)
	{
		printf("%s------>%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

// export should place the exported in the alphabetical order

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

void	ft_free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	d_node(t_env	**env_args, char *to_delete)
{
	t_env *tmp[3]; 

	tmp[0] = *env_args;
	tmp[1] = *env_args;
	while (tmp[0])
	{
		if (!ft_strcmp(tmp[0]->key, to_delete, ft_strlen(to_delete)))
		{
			tmp[2] = tmp[0]->next;
			break;
		}
		tmp[0] = tmp[0]->next;
	}
	while (tmp[1])
	{
		if (tmp[1]->next)
			if (!ft_strcmp(tmp[1]->next->key, to_delete, ft_strlen(to_delete)))
			{
				ft_free_node(tmp[1]->next);
				tmp[1]->next = tmp[2];
				break;
			}
		tmp[1] = tmp[1]->next;
	}
}

void	unset(t_list	*lst)
{
	t_env	*tmp;

	tmp = lst->env_args;
	if (!lst->cmd[1])
		return ;
	d_node(&tmp, lst->cmd[1]);
}