/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:12:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/04 16:55:21 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "tools.h"
#include <stddef.h> // for size_t to be recognized
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_cmd
{
    char **str;
}   t_cmd;

/*          BUILTINS        */

void    echo(char   **cmd);
void    cd(char **cmd);
void    pwd(char **str);

#endif