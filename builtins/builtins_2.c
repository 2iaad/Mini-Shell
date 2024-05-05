/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/05 20:19:39 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// better work with linked list in the env command to put each variable in its node 
// the node will contain the variable and its argument
// add the ft_lstnew and ft_lst_add_back to tools files
// then do the expanding
// each string expaned will get added to the cmd->env list
// check if there is $VAR and replace VAR with its value

void    env(t_cmd *cmd) // didnt handle "no envirement" case!!
{
    int i;
    char **str;
    char *argument;
    
    i = 0;
    while (cmd->env[i])
    {
        str = ft_split(cmd->env[i], '='); // i split with '=' and take the variable name
        argument = getenv(str[0]); // pass it to getenv to take its value
        ft_putstr(str[0]); // print variable
        write(1, "---->", 5);
        ft_putstr(argument); // print value
        write(1, "\n", 1);
        ft_free(str);
        i++;
    }
}