/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:56:52 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/20 10:13:30 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 // ****TO DO****
// 1. continue TOKENIZER
// 2. STRUCT
// 3. REMOVE QUOTES
// 4. GARVAGE COLLECTOR
// 5. NORMINETTE

char	*parse_protec(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (valid_meta(&line[i], i, 0, 1))
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				line[i] = -2;
				line[i + 1] = -2;
				i++;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				line[i] = -4;
				line[i + 1] = -4;
				i++;
			}
			else if (line[i] == '|')
				line[i] = -5;
			else if (line[i] == '<')
				line[i] = -1;
			else if (line[i] == '>')
				line[i] = -3;
		}
		i++;
	}
	return (line);
}


void print_struct(t_token *token)
{
	t_token *tmp_token = token;
	while (tmp_token)
	{
		printf("token: %s, type: ", tmp_token->token);
		switch (tmp_token->type)
		{
			case (0):
				printf("WORD\n");
				break ;
			case (1):
				printf("PIPE\n");
				break ;
			case (2):
				printf("REDIR_IN\n");
				break ;
			case (3):
				printf("REDIR_OUT\n");
				break ;
			case (4):
				printf("REDIR_APPEND\n");
				break ;
			case (5):
				printf("REDIR_HEREDOC\n");
				break ;
		}
		tmp_token = tmp_token->next;
	}
}
int	parce_line(char *line, t_env **env)
{
	char	*tmp;
	t_token	*token;
	token = NULL;
	char	**split = NULL; // to free the line

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
	if (syntax_error(line))
		return (1);
	line = parse_protec(line);
	line = expand_env(line, env);
	split = split_line(line);
	tokenizer(split, &token);
	print_struct(token);
	free(tmp);
	return (0);
}
// $x > out = ls -la > out > s
// $x: cmd
// > : redir_out
// out: out_file

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
