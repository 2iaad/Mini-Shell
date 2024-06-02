/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 15:29:03 by zderfouf         ###   ########.fr       */
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

void	builtins(t_list *lst)
{
    if (!ft_strncmp(lst->cmd[0], "echo", 4))
        echo(lst);
    if (!ft_strncmp(lst->cmd[0], "cd", 2))
        cd(lst);
    if (!ft_strncmp(lst->cmd[0], "pwd", 3))
        pwd();
    if (!ft_strncmp(lst->cmd[0], "export", 6))
        export_command(lst);
    if (!ft_strncmp(lst->cmd[0], "unset", 5))
        unset(lst);
    if (!ft_strncmp(lst->cmd[0], "env", 3))
        env(lst);
    if (!ft_strncmp(lst->cmd[0], "exit", 4))
        exit_command(lst->cmd);
}

void f()
{
    system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
    // atexit(f);
    t_list *lst;
	char *line;

    lst = malloc(sizeof(t_list));
	if (!lst)
		return (1);
	init_env(lst, env);

	while (1)
	{
		line = readline("--->");
		lst->cmd = ft_split(line, ' ');
		free(line);
		if (!lst->cmd[0])
			return(1);
		builtins(lst);
		ft_free(lst->cmd);
	}
	ft_lstclear(&lst->env);
    free(lst);
}