/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/04 17:07:38 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

// char	**merg_cmd(t_final	*lst)
// {
// 	int		i;
// 	char	**full_cmd;

// 	i = 0;
// 	while ((lst)->args && ((lst))->args[i]) // check if (lst)->args true incase there was only one argument "ls" there wont be any args then
// 		i++;
// 	full_cmd = (char **) malloc (sizeof(char *) * (i + 2));
// 	full_cmd[0] = ft_strdup((lst)->cmd);
// 	i = 0;
// 	while ((lst)->args && (lst)->args[i])
// 	{
// 		full_cmd[i + 1] = ft_strdup((lst)->args[i]);
// 		i++;
// 	}
// 	full_cmd[i + 1] = NULL;
// 	return (full_cmd);
// }

// void	init_final_cmd(t_final **lst)
// {
// 	char **str;

// 	t_final	*tmp = *lst;
// 	while (tmp)
// 	{
// 		str = merg_cmd(tmp);
// 		(tmp)->final_cmd = str;
// 		(tmp) = (tmp)->next;
// 	}
// }

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


	// while (lst)
	// {
	// 	if (pipe(fds) == -1)
	// 		perror("pipe");
	// 	pid = fork();
	// 	if (pid == -1)
	// 		perror("fork");
	// 	if (!pid)
	// 	{
	// 		close(fds[0]);
	// 		dup2(fds[1], 1);
	// 		close(fds[1]);
	// 		if (builtins(lst, env))
	// 		{
	// 			puts("HEERE\n\n\n");
	// 			exit(0);
	// 		}
	// 		else
	// 			execute_cmd(lst, envp);
	// 	}
	// 	else
	// 	{
	// 		dup2(fds[0], 0);
	// 		close(fds[0]);
	// 		close(fds[1]);
	// 		while (wait(NULL) == -1)
	// 			;
	// 	}
	// 	lst = lst->next;
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
