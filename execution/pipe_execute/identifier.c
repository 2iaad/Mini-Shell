/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/06 21:18:26 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	builtins(t_final *lst, t_env *env_list)
{
	bool	flag;

	flag = false;
    if (!ft_strncmp(lst->final_cmd[0], "echo", 4))
        echo(lst), flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "cd", 2))
        cd(lst, &env_list), flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "pwd", 3))
        pwd(), flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "export", 6))
        export_command(lst, &env_list), flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "unset", 5))
        unset(lst, env_list), flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "env", 3))
        env(lst, env_list), flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "exit", 4))
        exit_command(lst->final_cmd), flag = true;
	return (flag);
}

void	pipe_cmd(t_final *lst, int *fds, int flag)
{
	if (flag == 0)
		if (lst->next)
			pipe(fds);
	if (flag == 1)
		if (lst->next)
			{
				dup2(fds[1], 1);
				close(fds[0]);
				close(fds[1]);
			}
	if (flag == 2)
		if (lst->next)
		{
			dup2(fds[0], 0);
			close(fds[0]);
			close(fds[1]);	
		}
}

void    execution(t_final *lst, t_env *env, char **envp)
{
	int	pid;
	int	fds[2] = {1337, 1337};
	int	sec_fd[2];

	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
	while (lst)
	{
		pipe_cmd(lst, &fds[0], 0);
		pid = fork();
		if (!pid)
		{
			if (lst->in_file || lst->out_file)
			{
				infile_opener(lst->in_file);
				outfile_opener(lst->out_file);
			}
			else
				pipe_cmd(lst, &fds[0], 1);
			execute_cmd(lst, envp);
		}
		else
		{
			pipe_cmd(lst, &fds[0], 2);
			while (wait(NULL) == -1)
				;
			lst = lst->next;
		}
	}
	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
		perror("perror");
}

