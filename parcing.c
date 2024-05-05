/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:10:41 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/05 20:50:14 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parce_line(char *line, t_env **env)
{
	(void)env;
	if (!check_quotes(line))
	{
		free (line);//, ("syntax error\n"));
		printf("syntax error\n");
	}
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
int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_env *env;
	read_from_input(&env);
}