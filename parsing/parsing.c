/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:56:52 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/27 19:57:29 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**str;
	t_final	*tmp;

	tmp = *(*lst);
	while (tmp)
	{
		str = merg_cmd(tmp);
		(tmp)->final_cmd = str;
		(tmp) = (tmp)->next;
	}
}

void	reset_quotes(t_token **token)
{
	t_token	*node;
	int		i;

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
	char	**split;

	(1) && (tmp = NULL, token = NULL, split = NULL);
	if (!check_quotes(line))
	{
		ft_putstr_fd("syntax error related to unclosed quote\n", 2);
		return (-1);
	}
	(1) && (tmp = line, line = trim_line(line));
	if (line == NULL)
		return (-1);
	line = space(line, 0, 0);
	if (syntax_error(line))
	{
		exit_status(258, 1);
		return (-1);
	}
	split = split_line(line);
	tokenizer(split, &token, env);
	(1) && (read_herdoc(token),token_quotes(&token), split = split);
	(1) && (reset_quotes(&token), *final_cmd = struct_init(&token));
	init_final_cmd(&final_cmd);
	return (1);
}

void	read_from_input(t_final *final_cmd, t_env **env_list, char **envp)
{
	struct termios	p;
	char			*line;

	tcgetattr(0, &p);
	tcsetattr(0, 0, &p);
	printf("\nWelcome to minishell Program.\nMade by ibouram and zdefouf.\n");
	rl_catch_signals = 0;
	init_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line || !isatty(0))
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		if (g_signal == 2)
			g_signal = 0;
		add_history(line);
		if (parce_line(&final_cmd, *env_list, line) != -1)
			execution(final_cmd, env_list);
	}
}
