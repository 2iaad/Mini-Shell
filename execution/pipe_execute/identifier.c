/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/06 16:38:28 by zderfouf         ###   ########.fr       */
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
	int	fds[2];
	int	sec_fd[2];
	int	pid;
// ls > 1 > 2 > 23 > 3 > >>23 =====> exit from parsing
// echo salam > a > b | wc --> error
	sec_fd[0] = dup(0);
	sec_fd[1] = dup(1);
	while (lst)
	{
		if (lst->next)
			pipe(fds);
		pid = fork();
		if (!pid)
		{
			infile_opener(lst->in_file);
			outfile_opener(lst->out_file); // the problem here hiya ana kan dupi outfile m3a l stdout o lstdout kitlef
			// makanb9ach 9ad nkteb f pipe 7it aslan stdout talf makinch --> donc khasni nkhabih 
			if (lst->next)
			{
				dup2(fds[1], 1);
				close(fds[0]);
				close(fds[1]);
			}
			execute_cmd(lst, envp);
		}
		else
		{
			if (lst->next)
			{
				dup2(fds[0], 0);
				close(fds[0]);
				close(fds[1]);	
			}
			while (wait(NULL) == -1)
				;
			lst = lst->next;
		}
	}
	dup2(sec_fd[0], 0);
	dup2(sec_fd[1], 1);
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