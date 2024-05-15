/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:10:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/15 10:10:47 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

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
