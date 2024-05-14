/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/14 13:40:11 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// void	export_replace(t_env, char *)
// {
	
// }

void	export_join(t_env *env, char **key)
{
	char	*tmpo;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key[0], ft_strlen(key[0]) - 2))
		{
			printf("\nsalam\n");
			tmpo = tmp->value;
			tmp->value = ft_strjoin(tmpo, key[1]);
			free(tmpo);
		}
		tmp = tmp->next;
	}
}

void	export_solo(t_env *env)
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
		return export_solo(tmp);
	str = custumized_ft_split(lst->cmd[1], '=');
	if (!str)
		return ;
	if (str[0][ft_strlen(str[0]) - 1] == '+') // case where there is "+=" --> join
		export_join(lst->env, str);
	else if (str[1][0] == '+')
		printf("ndir function likatramplace dakchi b new content");
	else
		ft_lstadd_back(&lst->env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
	ft_free(str);
}
