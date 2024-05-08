/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/08 12:46:58 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

void	cmd_identifyer(t_list *lst)
{
    if (!ft_strcmp(lst->cmd[0], "echo", 4))
        echo(lst->cmd);
    if (!ft_strcmp(lst->cmd[0], "cd", 2))
        cd(lst->cmd);
    if (!ft_strcmp(lst->cmd[0], "pwd", 3))
        pwd();
    if (!ft_strcmp(lst->cmd[0], "export", 6))
        export_data(lst);
    // if (!ft_strcmp(lst->cmd[0], "unset"))
    //     unset(lst->cmd);
    if (!ft_strcmp(lst->cmd[0], "env", 3))
        env(lst);
    // if (!ft_strcmp(lst->cmd[0], "exit"))
    //     exit(lst->cmd);
}

void f()
{
    system("leaks minishell");
}

// better work with linked list in the env command to put each variable in its node 

int main(int ac, char **av, char **env)
{
    atexit(f);
    t_list *lst;

    lst = malloc(sizeof(t_list));
    lst->env = env;
	lst->env_args = NULL;
	/*			CD			*/
    // lst->cmd = ft_split("cd /tmp", ' ');
    // lst_identifyer(lst->cmd);
	
	/*			PWD			*/
    // lst->cmd = ft_split("pwd includes", ' ');
    // lst_identifyer(lst->cmd);

	/*			env			*/
    // lst->cmd = ft_split("env ", ' ');
    // cmd_identifyer(lst);
	// ft_free(lst->cmd);

	/*			export			*/
    lst->cmd = ft_split("export A13=37", ' ');
    cmd_identifyer(lst);
    ft_free(lst->cmd);
    lst->cmd = ft_split("export B=ziad", ' ');
    cmd_identifyer(lst);
    ft_free(lst->cmd);
	
    // lst->cmd = ft_split("env ", ' ');
    // cmd_identifyer(lst);
	// ft_free(lst->cmd);
	
	
	ft_lstclear(&lst->env_args);
    free(lst);
}