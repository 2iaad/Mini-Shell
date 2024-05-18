/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:56:52 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/14 01:13:47 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parce_line(char *line, t_env **env)
{
	char *tmp; // to free the line

	if (!check_quotes(line))
	{
		free (line);
		ft_putstr_fd("syntax error related to unclosed quote\n", 2);
		return (0);
	}
	tmp = line;
	line = trim_line(line);
	if (line == NULL)
		return (1);
	line = space(line, 0, 0);
	syntax_error(line);
	expand_env(line, env);
	free(tmp);
	return (0);
}

void	read_from_input(t_env **env)
{
	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		//displays the prompt "minishell$ " and waits for the user to enter a command. 
		// The entered command is stored in the line variable as a dynamically allocated string.
		if (!line)//If the user presses Ctrl-D, the program should exit. this if the user wanna exit
		{
			printf("exit\n");
			exit(0);
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		parce_line(line, env);
	}
}
// void f(void)
// {
// 	system("leaks minishell");
// }
int main(int ac, char **av, char **envp)
{
	// atexit(f);
	// rl_catch_signals = 0;
	if (ac > 1)
	{
		write(2, "Error: too many arguments\n", 26);
		return (1);
	}
	(void)av;
	t_env *env;
	env = get_env(envp);
	read_from_input(&env);
}
