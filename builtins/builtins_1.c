/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/13 16:29:30 by zderfouf         ###   ########.fr       */
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
		if (!ft_strcmp(tmp->key, arg, ft_strlen(arg)))
			printf("%s", tmp->value);
		tmp = tmp->next;
	}
}

void	exit_status_and_pid(char *str)
{
	
}

void    echo(t_list	*lst) // handle "echo -n -n"
{
	int	i;
    int	flag;

	if (!lst->cmd[1])
		return (void) write(1, "\n", 1);
	i = 1;
    flag = flag_check(lst->cmd[1]);
	while (lst->cmd[i]) // skip the "-n" "-n" if there are ones
	{
		if (flag_check(lst->cmd[i]))
			break ;
		i++;
	}
	while (lst->cmd[i]) // printf the strings that come after the "-nn"
	{
		if (lst->cmd[i][0] == '$')
		{
			if (lst->cmd[i][1] == '$') // need to handle the "echo $$$ ..."
				printf("khasni mprinti current pid, bach law3lm"); // increment i in the function by 2
			if (lst->cmd[i][1] == '?')
				printf("khasni mprinti exit status deyal last command executed"); // increment i in the function by 2
			else
				expand(lst, &lst->cmd[i][1]);
		}
		else if (lst->cmd[i][0] != '$')
			printf("%s", lst->cmd[i]);
		if (lst->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag) // if there is no flag (flag != 0) then write "\n"
		printf("\n");
}

void    cd(char **cmd)
{
    char *c_path;
    if (!access(cmd[1] , F_OK)) // === true
    {
        if (chdir(cmd[1]) == -1) // === then go to 
            perror("chdir");
    }
    else
        perror("cd");
}

void    pwd(void)
{
    char *c_path;

    c_path = getcwd(NULL, -1337); // when giving NULL , the fun ignores the number of bytes of the array that have been given
    if (!c_path) // contains the path, that have been allocated by getcwd
        perror("getcwd"); // return 
    ft_putstr(c_path, 1);
    free(c_path);
}
