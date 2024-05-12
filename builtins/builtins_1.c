/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:17:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/12 15:01:54 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand(t_list	*lst, char *arg)
{
	t_env	*tmp;

	tmp = lst->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, arg, ft_strlen(arg)))
			printf("%s", tmp->value);
		tmp = tmp->next;
	}
}

void    echo(t_list	*lst) // handle "echo -n -n"
{
    int flag;

    flag = 0;
    if (lst->cmd[1] == NULL) // echo 
        return (void) write(1, "\n", 1);
	if (!flag_check(lst->cmd[1])) // echo -n and echo -nnnnnn
	{
		if (lst->cmd[2])
			ft_putstr(lst->cmd[2], 1);
	}
	else
	{
		if (lst->cmd[1][0] == '$' && (lst->cmd[1][1] != '$' && lst->cmd[1][1] != '?')) // ila kan lst->cmd[1] o lst->cmd[1][0] = '$' => expand
			expand(lst, lst->cmd[1] + 1);
		else
			ft_putstr(lst->cmd[1], 1); // else echo string
	}
	if (flag_check(lst->cmd[1]))
		write(1, "\n", 1);
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
