/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:02:14 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/22 05:05:07 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtin_checker(t_final	**lst)
{
	char **str;
	
	if (!(*lst)->final_cmd[0] || !(*lst)->final_cmd[0][0])
		return ;
	str = ft_split((*lst)->cmd, ' ');
	if (!str || !str[0] || !str[1])
		return ;
	if (str[1])
	{
		ft_free((*lst)->final_cmd);
		(*lst)->final_cmd = str;
	}
	else
		ft_free(str);
}

bool	builtins(t_final *lst, t_env **env_list)
{
	if (!lst->final_cmd[0])
		return false;
	builtin_checker(&lst); // incase there was export x="export y=salam"
    if (!ft_strncmp(lst->final_cmd[0], "echo", 4))
        return (echo(lst, *env_list), (true));
    if (!ft_strncmp(lst->final_cmd[0], "cd", 2))
        return (cd(lst, *env_list), (true));
    if (!ft_strncmp(lst->final_cmd[0], "pwd", 3))
        return (pwd(*env_list), (true));
    if (!ft_strncmp(lst->final_cmd[0], "export", 6))
        return (export_command(lst, env_list), (true));
    if (!ft_strncmp(lst->final_cmd[0], "unset", 5))
        return (unset(lst, env_list), (true));
    if (!ft_strncmp(lst->final_cmd[0], "env", 3))
        return (env(lst, *env_list), (true));
    if (!ft_strncmp(lst->final_cmd[0], "exit", 4))
        return (exit_command(lst->final_cmd), (true));
	return (false);
}