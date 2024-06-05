/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/05 11:39:01 by zderfouf         ###   ########.fr       */
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

void    execution(t_final *lst, t_env *env, char **envp)
{
	int i;
	int	fds[2];
	int	pid;

	while (lst)
	{
		pid = fork();
		if (!pid)
		{
			infile_opener(lst->in_file);
			outfile_opener(lst->out_file);
			if (builtins(lst, env))
			{
				puts("## builtin ##\n");
				exit(0);
			}
			execute_cmd(lst, envp);
		}
		else
		{
			while (wait(NULL) == -1)
				;
			lst = lst->next;
		}
	}

	
	// while (lst)
	// {
	// 	if (pipe(fds) == -1)
	// 		perror("pipe");
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		if (lst->next)
	// 		{
	// 			close(fds[0]);
	// 			dup2(fds[1], 1);
	// 			close(fds[1]);
	// 		}
	// 		if (builtins(lst, env))
	// 			exit(0);
	// 		execute_cmd(lst, envp);
	// 	}
	// 	else
	// 	{
	// 		if (lst->next)
	// 		{
	// 			dup2(fds[0], 0);
	// 			close(fds[0]);
	// 			close(fds[1]);
	// 		}
	// 		while (wait(NULL) == -1)
	// 			;
	// 		lst = lst->next;
	// 	}
	// }
}


/*		PRINT FINAL CMD		*/

	// while (lst)
	// {
	// 	i = 0;
	// 	while (lst->final_cmd[i])
	// 	{
	// 		printf("---->%s", lst->final_cmd[i]);
	// 		i++;
	// 	}
	// 	printf("\n");
	// 	lst = lst->next;	
	// }