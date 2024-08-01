/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:49:51 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/01 12:29:22 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_error(char *cmd)
{
	write (2, "minishell: exit: ", 17);
	ft_putstr_fd(cmd, 2);
	write (2, ": numeric argument required\n", 28);
	exit(255);
}

void	exit_command(char **cmd)
{
	int	i;
	int	status;

	i = -1;
	status = exit_status(1, 0);
	if (cmd && cmd[0] && !cmd[1])
		exit(status);
	if (cmd && cmd[0] && cmd [1] && cmd[2])
		return (ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2));
	write(1, "exit\n", 5);
	if (cmd && cmd[0] && !cmd[1][0])
		return exit_error(cmd[1]);
	if (cmd && cmd[0] && cmd[1])
	{
		while (cmd[1] && cmd[1][++i])
		{
			if (!ft_isnum(cmd[1][i]))
			{
				exit_error(cmd[1]);
			}
		}
		exit(ft_atol(cmd[1]));
	}
}
