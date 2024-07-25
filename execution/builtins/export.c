/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/25 15:34:12 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_action(t_final *lst, t_env **env_list, char **str)
{
	if (str[0][ft_strlen(str[0]) - 1] == '+') // case where there is "+=" --> join
		export_join(*env_list, str);
	else if (str[1] && str[1][0] == '+') // case where there is "=+" --> replace // checking if str[1] in case i did "export salam"
		export_replace(*env_list, str);
	else
		export_var(*env_list,str);
}


void	export_helper(t_env **env_list, bool flag)
{
	if (!flag)
		init_exitstatus(env_list, EXIT_SUCCESS, 0);
	else
		init_exitstatus(env_list, EXIT_FAILURE, 0);
}

void	export_command(t_final *lst, t_env **env_list) // doesnt have to work if the key is a number or '=' , have to be ranged between 'a' and 'z'
{
	int		i;
	bool	flag;
	char	**str;

	(1 == 1) && ((i = 0) && (flag = false));
	if (!lst->final_cmd[1])
		return (alpha_arrang(*env_list), export_solo(*env_list)); // if there is "export" arrang and print
	while (lst->final_cmd[++i])
	{
		str = custumized_ft_split(lst->final_cmd[i], '='); // str = {"a","salam", NULL}
		if (!str)
			return ;
		if (!export_valid_check(str[0], &env_list))
		{
			flag = true;
			ft_free(str);
			continue;
		}
		export_action(lst, env_list, str);
		ft_free(str);
	}
	export_helper(env_list, flag);
}
