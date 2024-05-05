/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/05 15:49:03 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

void    cmd_identifyer(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->str[0], "echo", 4))
        echo(cmd->str);
    if (!ft_strcmp(cmd->str[0], "cd", 2))
        cd(cmd->str);
    if (!ft_strcmp(cmd->str[0], "pwd", 3))
        pwd();
    // if (!ft_strcmp(cmd->str[0], "export"))
    //     export(cmd->str);
    // if (!ft_strcmp(cmd->str[0], "unset"))
    //     unset(cmd->str);
    if (!ft_strcmp(cmd->str[0], "env", 3))
        env(cmd);
    // if (!ft_strcmp(cmd->str[0], "exit"))
    //     exit(cmd->str);
}

void f()
{
    system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
    atexit(f);
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    cmd->env = env;
    // cmd->str = ft_split("cd /tmp", ' ');
    // cmd_identifyer(cmd->str);
    // cmd->str = ft_split("pwd includes", ' ');
    // cmd_identifyer(cmd->str);
    cmd->str = ft_split("env ", ' ');
    cmd_identifyer(cmd);
    ft_free(cmd->str);
    free(cmd);
}