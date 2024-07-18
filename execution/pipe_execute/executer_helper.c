/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:32:12 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/18 09:37:33 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdbool.h>

void	multiple_helper(int *sec_fd, int exit_status)
{
	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
		error("dup2", 1337);
	while (wait(&exit_status) != -1)
		;
	return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
}

void	init_secfds(int *sec_fd)
{
	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
	if (sec_fd[0] == -1 || sec_fd[1] == -1)
		error("dup", 1337);
}

