/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:03:34 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/20 06:57:52 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*								UNSET								*/

void	ft_free_node(t_env *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
}

void	free_first_node(t_env **env_list)
{
	t_env	*tmp;
	t_env	*to_delete;

	to_delete = *env_list;
	tmp = (*env_list)->next;
	
	to_delete->next = NULL;
	ft_free_node(to_delete);

	*env_list = tmp;
}

void	d_node(t_env	**env, char *to_delete)
{
	t_env *tmp[3]; 

	tmp[0] = *env;
	tmp[1] = *env;
	while (tmp[0])
	{
		if (!ft_strncmp(tmp[0]->key, to_delete, ft_strlen(to_delete)))
		{
			tmp[2] = tmp[0]->next;
			break;
		}
		tmp[0] = tmp[0]->next;
	}
	while (tmp[1])
	{
		if (tmp[1]->next)
			if (!ft_strncmp(tmp[1]->next->key, to_delete, ft_strlen(to_delete)))
			{
				ft_free_node(tmp[1]->next);
				tmp[1]->next = tmp[2];
				break;
			}
		tmp[1] = tmp[1]->next;
	}
}

void	unset(t_final	*lst, t_env **env_list)
{
	int		i;

	i = 1;
	if (!lst->final_cmd[1])
		return ;
	while (lst->final_cmd[i])
	{
		if (!ft_strncmp((*env_list)->key, lst->final_cmd[i], ft_strlen(lst->final_cmd[i]))) // ila kan dak arg f lwl dlinked list
		{
			free_first_node(env_list);
		}
		else
		{
			d_node(env_list, lst->final_cmd[i]); // ila kan arg lwst
		}
		i++;
	}
}