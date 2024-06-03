/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/03 23:21:57 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

void	merg_cmd(t_final	***lst)
{
	int		i;
	char	**full_cmd;

	i = 0;
	while ((*(*lst))->args && (*(*lst))->args[i]) // check if (*(*lst))->args true incase there was only one argument "ls" there wont be any args then
		i++;
	full_cmd = (char **) malloc (sizeof(char *) * (i + 2));
	full_cmd[0] = ft_strdup((*(*lst))->cmd);
	i = 0;
	while ((*(*lst))->args && (*(*lst))->args[i])
	{
		full_cmd[i + 1] = ft_strdup((*(*lst))->args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	(*(*lst))->final_cmd = full_cmd;
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
	merg_cmd(&lst); // function li kadir lia l final cmd 
    builtins(*lst);
}