/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:56:52 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/23 00:47:21 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// exit f syntx error + check herdoc
//cat << salam >>>
// << salam |
// cat <<< salam
#include "../minishell.h"

char	**merg_cmd(t_final	*lst)
{
	int		i;
	char	**full_cmd;

	i = 0;
	while ((lst)->args && ((lst))->args[i])
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

void    reset_quotes(t_token **token)
{
    t_token *node;
    int     i;

    node = *token;
    while (node)
    {
        i = 0;
        while (node->token && node->token[i])
        {
            if (node->token[i] == -1)
                node->token[i] = '\'';
            else if (node->token[i] == -2)
                node->token[i] = '\"';
            i++;
        }
        node = node->next;
    }
}

int	parce_line(t_final **final_cmd, t_env *env, char *line)
{
	char	*tmp;
	t_token	*token;
	token = NULL;
	char	**split = NULL; // to free the line

	if (!check_quotes(line))
	{
		free (line);
		ft_putstr_fd("syntax error related to unclosed quote\n", 2);
		return -1;
	}
	tmp = line;
	line = trim_line(line);
	if (line == NULL)
		return -1;
	line = space(line, 0, 0);
	// open herdoc
	if (syntax_error(line))
	
		return (-1);
	split = split_line(line);
	tokenizer(split, &token, env);
	// print_struct(token);
	read_herdoc(token);
	token_quotes(&token);
	reset_quotes(&token);
	*final_cmd = struct_init(&token);
	init_final_cmd(&final_cmd);
	free(tmp);
	return (1);
}

void	read_from_input(t_final *final_cmd, t_env *env_list, char **envp)
{
	char *line;

	printf("\nWelcome to minishell Program.\nMade by Legends ibouram and zdefouf.\n");
	printf("For more details, please visit https://github.com/2iaad/minishell.\n");
	rl_catch_signals = 0;
	init_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (parce_line(&final_cmd, env_list, line) != -1)
		{
			execution(final_cmd, env_list); // pass &env_list here
		}
	}
}
