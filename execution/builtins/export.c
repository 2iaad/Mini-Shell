/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/29 09:16:13 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_action(t_final *lst, t_env **env_list, char **str)
{
	if (str[0][ft_strlen(str[0]) - 1] == '+')
		export_join(*env_list, str);
	else if (str[1] && str[1][0] == '+')
		export_replace(*env_list, str);
	else
		export_var(*env_list, str);
}

void	export_helper(t_env **env_list, bool flag)
{
	if (!flag)
		exit_status(0, 1);
	else
		exit_status(1, 1);
}

void	export(t_env **env_list)
{
	t_env	*copy;

	env_copy(env_list, &copy);
	alpha_arrang(copy);
	export_solo(copy);
	ft_lstclear(&copy);
}

void	export_command(t_final *lst, t_env **env_list)
{
	int		i;
	bool	flag;
	char	**str;

	(1 == 1) && ((i = 0) && (flag = false));
	if (!lst->final_cmd[1])
		return (export(env_list));
	while (lst->final_cmd[++i])
	{
		str = custumized_ft_split(lst->final_cmd[i], '=');
		if (!str)
			return ;
		if (!export_valid_check(str[0], &env_list))
		{
			flag = true;
			ft_free(str);
			continue ;
		}
		(1) && (export_action(lst, env_list, str), ft_free(str), (i = i));
	}
	export_helper(env_list, flag);
}
