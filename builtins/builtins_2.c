/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/05 15:51:19 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    env(t_cmd *cmd)
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
        write(1, "=", 1);
        ft_putstr(argument); // print value
        write(1, "\n", 1);
        ft_free(str);
        i++;
    }
}