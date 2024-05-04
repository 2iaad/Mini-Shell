/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/04 16:01:45 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

void    cmd_identifyer(char **str)
{
    if (!ft_strcmp(str[0], "echo", 4))
        echo(str);
    if (!ft_strcmp(str[0], "cd", 2))
        cd(str);
    if (!ft_strcmp(str[0], "pwd", 3))
        pwd(str);
    // if (!ft_strcmp(str[0], "export"))
    //     export(str);
    // if (!ft_strcmp(str[0], "unset"))
    //     unset(str);
    // if (!ft_strcmp(str[0], "env"))
    //     env(str);
    // if (!ft_strcmp(str[0], "exit"))
    //     exit(str);
}

void f()
{
    system("leaks minishell");
}

int main()
{
    // atexit(f);
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    cmd->str = ft_split("cd /tmp", ' ');
    cmd_identifyer(cmd->str);
    cmd->str = ft_split("pwd includes", ' ');
    cmd_identifyer(cmd->str);
    free(cmd);
}