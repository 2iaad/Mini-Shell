/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/11 20:16:21 by zderfouf         ###   ########.fr       */
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

	tmp = lst->env; // to keep the linked list preserved for later freeing of the linked list
	while (tmp)
	{
		printf("%s------>%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
/* 								EXPORT								*/

void	alpha_arrang(t_env *env)
{
	char *temp;
	t_env *tmp;

	tmp = env;
	while (tmp && tmp->next)
	{
		if (tmp->key[0] > tmp->next->key[0])
		{
			temp = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = temp;
			tmp = env;
		}
		else
			tmp = tmp->next;
	}
}

void	solo_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_", 1))
			printf("declare -x %s=%s\n",tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	export_data(t_list *lst) // doesnt have to work if the key is a number or '=' , have to be ranged between 'a' and 'z'
{
	char	**str;
	t_env	*tmp;

	tmp = lst->env;
	alpha_arrang(tmp);
	if (!lst->cmd[1])
		return solo_export(tmp);
	str = custumized_ft_split(lst->cmd[1], '='); // it segf if there is no "="
	if (!str)
		return ;
	ft_lstadd_back(&lst->env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
	ft_free(str);
}

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
		
	d_node(&tmp, lst->cmd[1]);
}