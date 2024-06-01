/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/31 16:46:49 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_status(t_list	*lst, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			printf("khasni mprinti exit status deyal last command executed");
		i++;
	}
}

void    echo(t_list	*lst)
{
	int	i;
    int	flag;

	i = 1;
	if (!lst->cmd[1])
		return (void) write(1, "\n", 1);
    flag = flag_check(lst->cmd[1]);
	while (lst->cmd[i]) // skip the "-n" "-nnn" if there are ones
	{
		if (flag_check(lst->cmd[i]))
			break ;
		i++;
	}
	while (lst->cmd[i]) // printf the strings that come after the "-nn"
	{
		printf("%s", lst->cmd[i]);
		if (lst->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag) // if there is no flag (flag != 0) then write "\n"
		printf("\n");
}
