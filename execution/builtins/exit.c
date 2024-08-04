/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:49:51 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 02:40:04 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdbool.h>

void	exit_error(char *cmd)
{
	write (2, "minishell: exit: ", 17);
	ft_putstr_fd(cmd, 2);
	write (2, ": numeric argument required\n", 28);
	exit(255);
}

bool	check_if_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		if (!ft_isnum(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	spaces_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	error_checker(char *str)
{
	bool	flag;
	char	**s;;

	if (!str[0]) // ""
		return (true); 
	if (spaces_checker(str)) // "  "
		return (true);
	s = ft_split(str, ' ');
	if (s[1]) // "1  2"
		return (ft_free(s), true);
	ft_free(s);
	if (check_if_valid(str))
		return (true);
	ft_atol(str, &flag);
	if (flag)
		return (true);
	return (false);
}


void	exit_command(char **cmd)
{
	bool	flag;
	int		status;

	(1) && (flag = 0 ,status = exit_status(1, 0));
	if (!cmd[1]) // exit
		exit (status);
	if (error_checker(cmd[1])) // ila kan true donc kayn error f cmd[1]
		flag = 1;
	if (cmd[2] && flag) // exit 1d d
			return (void) write(1, "exit\n", 5), exit_error(cmd[1]);
	else if (cmd[2] && !flag) // exit 1 d
			return (ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2));
	else if (cmd[1] && flag)
			return (void) write(1, "exit\n", 5), exit_error(cmd[1]);
	else
	{
		printf("nparsi number\n");
	}
}
