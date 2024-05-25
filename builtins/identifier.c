/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/25 09:35:09 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// builltins need to work without execve, if there is a pipe i need to fork then call the builtin.

void	init_env(t_list *lst, char **env)
{
	int		i;
	char	**str;
	t_env	*tmp;

    i = 0;
	lst->env = NULL;
    while (env[i])
    {
        str = ft_split(env[i], '='); // i split with '=' and take the variable name
		ft_lstadd_back(&lst->env, ft_lstnew(ft_strdup(str[0]), ft_strdup(getenv(str[0])))); // strdup bec bla strdup makhdmatch ez
        ft_free(str);
        i++;
    }
}

void	cmd_identifyer(t_list *lst)
{
    if (!ft_strcmp(lst->cmd[0], "echo", 4))
        echo(lst);
    if (!ft_strcmp(lst->cmd[0], "cd", 2))
        cd(lst->cmd);
    if (!ft_strcmp(lst->cmd[0], "pwd", 3))
        pwd();
    if (!ft_strcmp(lst->cmd[0], "export", 6))
        export_data(lst);
    if (!ft_strcmp(lst->cmd[0], "unset", 5))
        unset(lst);
    if (!ft_strcmp(lst->cmd[0], "env", 3))
        env(lst);
    // if (!ft_strcmp(lst->cmd[0], "exit"))
    //     exit(lst->cmd);
}

void f()
{
    system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
    // atexit(f);
    t_list *lst;

    lst = malloc(sizeof(t_list));
	init_env(lst, env);

	while (1)
	{
		lst->cmd = ft_split(readline("----->"), ' ');
		if (!lst->cmd[0]) // if (readline return NULL)
			return(1);
		cmd_identifyer(lst);
		ft_free(lst->cmd);
	}

	ft_lstclear(&lst->env);
    free(lst);
}