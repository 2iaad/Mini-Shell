/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/25 11:00:02 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdbool.h>

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

void	export_replace(t_env *env, char **str)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str[0], ft_strlen(str[0])))
		{
			free(tmp->value); // free old value
			tmp->value = ft_strdup(str[1]); // replace it with new allocated value(so i can free the linked list)
		}
		tmp = tmp->next;
	}	
}

void	export_join(t_env *env, char **str)
{
	char	*tmpo;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str[0], ft_strlen(str[0]) - 2))
		{
			tmpo = tmp->value;
			tmp->value = ft_strjoin(tmpo, str[1]);
			free(tmpo);
		}
		tmp = tmp->next;
	}
}

void	export_var(t_env *env, char **str)
{
	bool	flag;
	t_env	*tmp;

	flag = false;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str[0], ft_strlen(str[0])))
		{
			flag = true; // flag tells if there is the variable or it should be added
			free(tmp->value);
			tmp->value = ft_strdup(str[1]);
		}
		tmp = tmp->next;
	}
	if (flag == false) // ila mal9ach smit lvariable ay addih
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
}

void	export_solo(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_", 1))
			printf("declare -x %s=\"%s\"\n",tmp->key, tmp->value); // \" to print the double quotations
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
		return export_solo(tmp);
	
	str = custumized_ft_split(lst->cmd[1], '=');
	if (!str)
		return ;
	if (str[0][ft_strlen(str[0]) - 1] == '+') // case where there is "+=" --> join
		export_join(lst->env, str);
	else if (str[1][0] == '+') // case where there is "=+" --> replace
		export_replace(lst->env, str);
	else
		export_var(lst->env,str);
	ft_free(str);
}
