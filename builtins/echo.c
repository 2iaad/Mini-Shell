/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/25 16:39:14 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand(t_list	*lst, char *arg)
{
	t_env	*tmp;

	tmp = lst->env;
	if (!ft_strlen(arg)) // in case there is only "$"
		printf("$");
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, arg, ft_strlen(arg)))
			printf("%s", tmp->value);
		tmp = tmp->next;
	}
}

void	echo_helpler(t_list	*lst, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i++;
		else if (str[i] == '?')
			printf("khasni mprinti exit status deyal last command executed");
		else
			expand(lst, &str[i]);
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
		if (lst->cmd[i][0] == '$')
			echo_helpler(lst, &lst->cmd[i][0] + 1); // (& + 1) to give the string starting from the next character
		else if (lst->cmd[i][0] != '$')
			printf("%s", lst->cmd[i]);
		if (lst->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag) // if there is no flag (flag != 0) then write "\n"
		printf("\n");
}
