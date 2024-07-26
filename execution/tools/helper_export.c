/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:49:11 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/26 15:49:00 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void	export_replace(t_env *env, char **str)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str[0], ft_strlen(str[0])))
		{
			free(tmp->value); // free old value
			tmp->value = ft_strdup(str[1]); // replace it with new allocated value(so i can free the linked list)
		}
		tmp = tmp->next;
	}	
}

void	export_join(t_env *env, char **str)
{
	bool	flag;
	t_env	*tmp;
	char	*tmpo;

	flag = false;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str[0], ft_strlen(str[0]) - 2))
		{
			flag = true;
			tmpo = tmp->value;
			tmp->value = ft_strjoin(tmpo, str[1]);
			free(tmpo);
		}
		tmp = tmp->next;
	}
	if (flag == false) // ila mal9ach smit lvariable ay addih
	{
		str[0][ft_strlen(str[0]) - 1] = '\0'; // atkoun str[0]="a+" donc blast + andir '\0' 3ad naddih
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
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
		if (!ft_strncmp(tmp->key, str[0], ft_strlen(str[0])))
		{
			flag = true;
			if (tmp->value && !str[1]) // ila kant "export a=salam a"
				break ;
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
		if (ft_strncmp(tmp->key, "_", 1) && ft_strncmp(tmp->key, "?", 1))
		{
			if (tmp->value && *tmp->value)
				printf("declare -x %s=\"%s\"\n",tmp->key, tmp->value); // \" to print the double quotations
			else if (tmp->value && !*tmp->value) 
				printf("declare -x %s=\"\"\n",tmp->key); // incase there was a "export VAR="
			else
				printf("declare -x %s\n", tmp->key); // hadi ila makanch chi key ando value deyalo
		}
		tmp = tmp->next;
	}
	init_exitstatus(&env, 0, 0);
}

void	env_copy(t_env **env_list, t_env **copy)
{
	t_env *tmpo;

	tmpo = *env_list;
	*copy = NULL;
	while (tmpo)
	{
		ft_lstadd_back(copy, ft_lstnew(ft_strdup(tmpo->key), ft_strdup(tmpo->value)));
		tmpo = tmpo->next;
	}
}