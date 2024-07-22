/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:32:12 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/22 01:17:19 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple_helper(t_env ***env, int *sec_fd, int exit_status)
{
	t_env	*tmp;

	tmp = *(*env);
	while (wait(&exit_status) != -1)
		;
	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
		error("dup2", 1337);
	return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
}

void	init_secfds(int *sec_fd)
{
	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
	if (sec_fd[0] == -1 || sec_fd[1] == -1)
		error("dup", 1337);
}

void	init_exitstatus(t_env **env, int flag, int exit_status)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "?", 1))
		{
			free(tmp->value);
			if (flag == 0)
				tmp->value = ft_strdup("0");
			else if (flag == 1)
				tmp->value = ft_strdup("1");
			else
			 	tmp->value = ft_itoa(exit_status);
		}
		tmp = tmp->next;
	}
}