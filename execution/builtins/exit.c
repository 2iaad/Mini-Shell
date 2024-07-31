/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:49:51 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/31 16:25:35 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_command(char **cmd)
{
	int	i;
	int	status;

	i = -1;
	status = exit_status(1, 0);
	if (cmd[2])
		return (ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2));
	while (cmd[1] && cmd[1][++i])
	{
		if (!ft_isnum(cmd[1][i]))
		{
			write(1, "exit\n", 5);
			write (2, "minishell: exit: ", 17);
			ft_putstr_fd(cmd[1], 2);
			write (2, ": numeric argument required\n", 28);
			exit(255);
		}
	}
	write(1, "exit\n", 5);
	if (cmd[1])
		exit(ft_atol(cmd[1]));
	else
		exit(status);
}
