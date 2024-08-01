/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:32:12 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/01 17:45:50 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple_helper(t_env **env)
{
	int	status;

	if (g_signal)
		return (g_signal = 0, (void) NULL);
	while (wait(&(status)) != -1)
		;
	exit_status(WEXITSTATUS(status), 1);
}

void	init_secfds(int *sec_fd, int flag)
{
	if (flag == 0)
	{
		(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
		if (sec_fd[0] == -1 || sec_fd[1] == -1)
			error("dup", 1337);
	}
	else
	{
		if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
			error("dup2", 1337);
		return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
	}
}

void	env_maker(t_env *envp, char ***env)
{
	int		i;
	char	*str;
	t_env	*tmp;

	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	*env = (char **) gv_coll (sizeof(char *) * (i + 1));
	if (!*env)
		return ;
	(1 == 1) && ((tmp = envp) && (i = 0));
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		(*env)[i] = ft_strjoin(str, tmp->value);
		free(str);
		tmp = tmp->next;
		i++;
	}
	(*env)[i] = NULL;
}

void	error(char *str, int a)
{
	if (a == 1)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	exit(1);
}
