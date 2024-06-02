/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:03:34 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 19:06:29 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	unset(t_list	*lst)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!lst->cmd[1])
		return ;
	while (lst->cmd[i])
	{
		if (!ft_strncmp(lst->env->key, lst->cmd[i], ft_strlen(lst->cmd[i]))) // ila kan dak arg f lwl dlinked list
		{
			tmp = lst->env;
			lst->env = lst->env->next;
			free(tmp);
		}
		else
			d_node(&lst->env, lst->cmd[i]); // ila kan arg lwst
		i++;
	}
}