/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/12 11:53:42 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	str = custumized_ft_split(lst->cmd[1], '=');
	if (!str)
		return ;
	ft_lstadd_back(&lst->env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
	ft_free(str);
}
