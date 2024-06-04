/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:56:52 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/04 17:05:08 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// ****TO DO****

// 5. NORMINETTE
// 6. SIGNALS
// 7. exit status
// $d | ls
//export A="d d" | echo $A
// z"" z " "
//  sss $USER_ SS

char	**merg_cmd(t_final	*lst)
{
	int		i;
	char	**full_cmd;

	i = 0;
	while ((lst)->args && ((lst))->args[i]) // check if (lst)->args true incase there was only one argument "ls" there wont be any args then
		i++;
	full_cmd = (char **) malloc (sizeof(char *) * (i + 2));
	full_cmd[0] = ft_strdup((lst)->cmd);
	i = 0;
	while ((lst)->args && (lst)->args[i])
	{
		full_cmd[i + 1] = ft_strdup((lst)->args[i]);
		i++;
	}
	full_cmd[i + 1] = NULL;
	return (full_cmd);
}

void	init_final_cmd(t_final ***lst)
{
	char **str;

	t_final	*tmp = *(*lst);
	while (tmp)
	{
		str = merg_cmd(tmp);
		(tmp)->final_cmd = str;
		(tmp) = (tmp)->next;
	}
}

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
				printf("CMD\n");
				break ;
			case (2):
				printf("OPTION\n");
				break ;
			case (3):
				printf("PIPE\n");
				break ;
			case (4):
				printf("REDIR_IN\n");
				break ;
			case (5):
				printf("REDIR_OUT\n");
				break ;
			case (6):
				printf("REDIR_APPEND\n");
				break ;
			case (7):
				printf("REDIR_HEREDOC\n");
				break ;
			case (8):
				printf("IN_FILE\n");
				break ;
			case (9):
				printf("OUT_FILE\n");
				break ;
			case (10):
				printf("AOUT_FILE\n");
				break ;
			case (11):
				printf("DELIMITER\n");
				break ;
		}
		tmp_token = tmp_token->next;
	}
}
void	parce_line(t_final **final_cmd, t_env *env, char *line)
{
	char	*tmp;
	t_token	*token;
	token = NULL;
	char	**split = NULL; // to free the line

	if (!check_quotes(line))
	{
		free (line);
		ft_putstr_fd("syntax error related to unclosed quote\n", 2);
		return ;
	}
	tmp = line;
	line = trim_line(line);
	if (line == NULL)
		return ;
	line = space(line, 0, 0);
	if (syntax_error(line))
		return ;
	line = parse_protec(line);
	line = expand_env(line, env);
	// if find expand_env should stop the program
	split = split_line(line);
	tokenizer(split, &token);
	token_quotes(&token);
	// print_struct(token);
	// exit(0);
	*final_cmd = struct_init(&token);
	init_final_cmd(&final_cmd);
	free(tmp);
}


void	read_from_input(t_final *final_cmd, t_env *env_list, char **envp)
{
	char *line;

	printf("\nWelcome to minishell Program.\nMade by Legends ibouram and zdefouf.\n");
	printf("For more details, please visit https://github.com/2iaad/minishell.\n");
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
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
		parce_line(&final_cmd, env_list, line);
		execution(final_cmd, env_list, envp); // pass &env_list here
	}
}

// {
// 	char *line;

// 	printf("\nWelcome to minishell Program.\nMade by Legends ibouram and zdefouf.\n");
// 	printf("For more details, please visit https://github.com/2iaad/minishell.\n");
// 	while (1)
// 	{
// 		// printf("\nWelcome to minishell Program.\nMade by Legends ibouram and zdefouf.\n");
// 		// printf("For more details, please visit https://github.com/2iaad/minishell.\n");
// 		line = readline("minishell$ ");
// 		//displays the prompt "minishell$ " and waits for the user to enter a command. 
// 		// The entered command is stored in the line variable as a dynamically allocated string.
// 		if (!line)//If the user presses Ctrl-D, the program should exit. this if the user wanna exit
// 		{
// 			printf("exit\n");
// 			exit(0);
// 		}
// 		if (!line[0])
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		parce_line(line, env);
// 	}
// }
// void f(void)
// {
// 	system("leaks minishell");
// }
// int main(int ac, char **av, char **envp)
// {
// 	t_final *final_cmd;
// 	// atexit(f);
// 	// rl_catch_signals = 0;
// 	if (ac > 1)
// 	{
// 		write(2, "Error: too many arguments\n", 26);
// 		return (1);
// 	}
// 	(void)av;
// 	t_env *env;
// 	env = get_env(envp);
// 	final_cmd = read_from_input(&env);
// 	// execution(final_cmd, &env);
// }
