/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:03:34 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/15 10:13:39 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*								UNSET								*/

void	ft_free_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	d_node(t_env	**env, char *to_delete)
{
	t_env *tmp[3]; 

	tmp[0] = *env;
	tmp[1] = *env;
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

	tmp = lst->env;
	if (!lst->cmd[1])
		return ;
	d_node(&tmp, lst->cmd[1]);
}