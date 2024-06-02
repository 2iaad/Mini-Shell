/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 22:36:51 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

// void	init_env(t_list *lst, char **env)
// {
// 	int		i;
// 	char	**str;

//     i = 0;
// 	lst->env = NULL;
//     while (env[i])
//     {
//         str = ft_split(env[i], '='); // i split with '=' and take the variable name
// 		ft_lstadd_back(&lst->env, ft_lstnew(ft_strdup(str[0]), ft_strdup(getenv(str[0])))); // strdup bec bla strdup makhdmatch ez
//         ft_free(str);
//         i++;
//     }
// }

void	builtins(t_final *lst)
{
    if (!ft_strncmp(lst->exec_cmd[0], "echo", 4))
        echo(lst);
    if (!ft_strncmp(lst->exec_cmd[0], "cd", 2))
        cd(lst);
    if (!ft_strncmp(lst->exec_cmd[0], "pwd", 3))
        pwd();
    if (!ft_strncmp(lst->exec_cmd[0], "export", 6))
        export_command(lst);
    if (!ft_strncmp(lst->exec_cmd[0], "unset", 5))
        unset(lst);
    if (!ft_strncmp(lst->exec_cmd[0], "env", 3))
        env(lst);
    if (!ft_strncmp(lst->exec_cmd[0], "exit", 4))
        exit_command(lst->exec_cmd);
}

void    execution(t_final *lst)
{
    char    **command;

    // function li ghadi naddi (char *)cmd --- (char **)args = command
    builtins(lst);
}