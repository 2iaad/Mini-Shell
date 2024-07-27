/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/27 17:46:37 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    echo(t_final	*lst)
{
	int	i;
    int	flag;

	i = 1;
	if (!lst->final_cmd[1])
		return (void) write(1, "\n", 1);
    flag = flag_check(lst->final_cmd[1]);
	while (lst->final_cmd[i]) // skip the "-n" "-nnn" if there are ones
	{
		if (flag_check(lst->final_cmd[i]))
			break ;
		i++;
	}
	while (lst->final_cmd[i]) // printf the strings that come after the "-nn"
	{
		ft_putstr_fd(lst->final_cmd[i], 1);
		if (lst->final_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag) // if there is no flag (flag != 0) then write "\n"
		write(1, "\n", 1);
	exit_status(0,1);
}
