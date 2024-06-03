/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/03 04:02:17 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

void	merg_cmd(t_final	**lst)
{
	int		i;
	int		j;
	char	**full_cmd;

	j = 0;
	i = 0;
	while ((*lst)->args[i])
		i++;
	full_cmd = malloc(sizeof(char *) * i + 2);
	full_cmd[0] = (*lst)->cmd;
	while ((*lst)->args[j])
	{
		full_cmd[j + 1] = (*lst)->args[j];
		j++;
	}
	full_cmd[j + 1] = NULL;
	(*lst)->final_cmd = full_cmd;
}

void	builtins(t_final *lst)
{
    if (!ft_strncmp(lst->final_cmd[0], "echo", 4))
        echo(lst);
    if (!ft_strncmp(lst->final_cmd[0], "cd", 2))
        cd(lst);
    if (!ft_strncmp(lst->final_cmd[0], "pwd", 3))
        pwd();
    if (!ft_strncmp(lst->final_cmd[0], "export", 6))
        export_command(lst);
    if (!ft_strncmp(lst->final_cmd[0], "unset", 5))
        unset(lst);
    if (!ft_strncmp(lst->final_cmd[0], "env", 3))
        env(lst);
    if (!ft_strncmp(lst->final_cmd[0], "exit", 4))
        exit_command(lst->final_cmd);
}


void    execution(t_final **lst)
{
	// merg_cmd(lst); // function li kadir lia l final cmd 
    // builtins(lst);
}