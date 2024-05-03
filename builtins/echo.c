/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/03 15:00:18 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    echo(char   **cmd)
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 1;
    flag = 0;
	if (!ft_strcmp(cmd[1], "-n"))
	{
		if (cmd[2])
			ft_putstr(cmd[2]);
	}
	else
	 	ft_putstr(cmd[1]);
	if (ft_strcmp(cmd[1], "-n"))
		write(1, "\n", 1);
}

void    identifyer(char **str)
{
    if (!ft_strcmp(str[0], "echo"))
        echo(str);
    // if (!ft_strcmp(str[0], "cd"))
    //     cd(str);
    // if (!ft_strcmp(str[0], "pwd"))
    //     pwd(str);
    // if (!ft_strcmp(str[0], "export"))
    //     export(str);
    // if (!ft_strcmp(str[0], "unset"))
    //     unset(str);
    // if (!ft_strcmp(str[0], "env"))
    //     env(str);
    // if (!ft_strcmp(str[0], "exit"))
    //     exit(str);
}

int main()
{
    char **str = ft_split("echo salam", ' ');
    identifyer(str);
}