/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/12 11:55:51 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    echo(char   **cmd) // handle "echo -n -n"
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 1;
    flag = 0;
    if (cmd[1] == NULL) // echo 
    {
        write(1, "\n", 1);
        return ;
    }
	if (!flag_check(cmd[1])) // echo -n and echo -nnnnnn
	{
		if (cmd[2])
			ft_putstr(cmd[2], 1);
	}
	else
	 	ft_putstr(cmd[1], 1); // echo string
	if (flag_check(cmd[1]))
		write(1, "\n", 1);
}

void    cd(char **cmd)
{
    char *c_path;
    if (!access(cmd[1] , F_OK)) // === true
    {
        if (chdir(cmd[1]) == -1) // === then go to 
            perror("chdir");
    }
    else
        perror("cd");
}

void    pwd(void)
{
    char *c_path;

    c_path = getcwd(NULL, -1337); // when giving NULL , the fun ignores the number of bytes of the array that have been given
    if (!c_path) // contains the path, that have been allocated by getcwd
        perror("getcwd"); // return 
    ft_putstr(c_path, 1);
    free(c_path);
}
