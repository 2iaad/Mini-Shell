/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/19 10:26:37 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	multiple(t_final *lst, t_env *env, char **envp)
// {
// 	pid_t	pid;
// 	int		exit_status;
// 	int		fds[2][2]; // fds[0] ---> fds[2] ###### fds[1] ----> sec_fd

// 	init_secfds(&fds[1][0]);
// 	while (lst)
// 	{
// 		pipe_cmd(lst, &fds[0][0], 0);
// 		if (lst->heredoc)
// 			heredoc_opener(lst->heredoc, env, fds[1][0]);
// 		pid = fork();
// 		if (pid == -1)
// 			error("fork", 1337);
// 		if (!pid)
// 			child(lst, env, fds[0], envp, fds[1][0]);
// 		else
// 		{
// 			pipe_cmd(lst, &fds[0][0], 2);
// 			lst = lst->next;
// 		}
// 	}
// 	multiple_helper(fds[1], exit_status);
// }


// void	single(t_final *lst, t_env *env, char **envp)
// {
// 	pid_t	pid;
// 	bool	flag;
// 	int		sec_fd[2];

// 	sec_fd[0] = dup(0);
// 	sec_fd[1] = dup(1);
// 	flag = false;
// 	single_redirect(lst, env);
// 	builtins(lst, env, &flag);
// 	if (!flag) // ila makantch command builtin
// 	{
// 		pid = fork();
// 		if (!pid)
// 			execute_cmd(lst, envp);
// 		else
// 		 	wait(NULL);
// 	}
// 	dup2(sec_fd[0], 0);
// 	dup2(sec_fd[1], 1);
	
// }

void	execution(t_final *lst, t_env *env, char **envp)
{
	// if (lst->next)
	// 	multiple(lst, env, envp);
	// else
	//  	single(lst, env, envp);
	while (lst)
	{
		printf("CMD: %s\n", lst->final_cmd[0]);
		printf("OPTIONS: ");
		for (int i = 1; lst->final_cmd[i]; i++)
			printf("%s ", lst->final_cmd[i]);
		printf("\n");
		if (lst->files)
		{
			int j = 0;
			while (lst->files[j].type != 42)
			{
				printf("file: %s\n", lst->files[j].file);
				printf("type: ");
				if (lst->files[j].type == 8)
					printf("IN_FILE\n");
				else if (lst->files[j].type == 9)
					printf("OUT_FILE\n");
				else if (lst->files[j].type == 10)
					printf("AOUT_FILE\n");
				else if (lst->files[j].type == 11)
					printf("DELIMITER\n");
				j++;
			}
				printf("ss\n");
		}
		printf("\n=========================================\n");
		lst = lst->next;
	}
}
