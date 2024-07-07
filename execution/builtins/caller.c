/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:02:14 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/07 10:00:54 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_checker(t_final	**lst)
{
	char **str;
	
	str = ft_split((*lst)->cmd, ' ');
	if (str[1])
	{
		ft_free((*lst)->final_cmd);
		(*lst)->final_cmd = str;
	}
	else
		ft_free(str);
}

void	builtins(t_final *lst, t_env *env_list, bool *flag)
{
	if (!lst->final_cmd[0])
		return ;
	cmd_checker(&lst); // incase there was export x="export y=salam"
    if (!ft_strncmp(lst->final_cmd[0], "echo", 4))
        echo(lst), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "cd", 2))
        cd(lst, &env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "pwd", 3))
        pwd(), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "export", 6))
        export_command(lst, &env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "unset", 5))
        unset(lst, env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "env", 3))
        env(lst, env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "exit", 4))
        exit_command(lst->final_cmd), *flag = true;
}