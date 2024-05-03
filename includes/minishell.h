/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:12:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/03 16:49:29 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "tools.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_cmd
{
    char *cmd;
    char *string;
}   t_cmd;

#endif