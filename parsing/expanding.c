/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 03:47:44 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/30 04:52:08 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status(int status, int set)
{
	static int	current_status;

	current_status = 0;
	if (set != 0)
		current_status = status;
	return (current_status);
}

char	*handle_num(char *line, int *i)
{
	int		var_len;
	char	*new_line;
	char	*new;

	var_len = 1;
	new = NULL;
	while (line[*i + var_len] && ft_isnum(line[*i + var_len]))
		var_len++;
	new_line = ft_substr(line, *i + 2, var_len - 2);
	new = ft_strjoin_parse(new, new_line);
	*i += var_len;
	return (new);
}

char	*expand_env(char *lin, t_env *env)
{
	t_parse	ps;
	int		a;
	t_env	*tmp_env;
	t_env	*expander;

	(1) && (ps.i = 0, ps.new = NULL, expander = NULL);
	while (lin[ps.i])
	{
		ps.len = 0;
		while (!(lin[ps.i + ps.len] == '$'
				&& vm2(lin, ps.i + ps.len, 0, 1)) && lin[ps.i + ps.len] != '\0')
			ps.len++;
		if (ps.len > 0)
			expand_env_1(&ps, lin, ps.i);
		if (check_dollar_condition(lin, ps.i, ps.len))
			expand_env_2(&ps, &ps.i);
		else if (lin[ps.i + ps.len] == '$'
			&& ft_isnum(lin[ps.i + ps.len + 1]))
			ps.new = handle_num(lin, &ps.i);
		else if (lin[ps.i + ps.len] == '$')
			handle_dollar(&ps, lin, env, &expander);
		else
			ps.i += ps.len;
	}
	return (ps.new);
}

int	expanding(t_token *token, t_env *env)
{
	t_token	*tmp_token;
	char	*tmp;
	int		prev_type;
	int		ambig_redirect;
	(1) && (tmp_token = token, prev_type = -1, ambig_redirect = 0);
	while (tmp_token)
	{
		if (tmp_token->type != REDIR_IN && tmp_token->type != REDIR_OUT
			&& tmp_token->type != REDIR_APPEND
			&& tmp_token->type != REDIR_HEREDOC && tmp_token->type != DELIMITER)
		{
			tmp = tmp_token->token;
			tmp_token->token = expand_env(tmp_token->token, env);
			// printf("----->%s", tmp_token->token);
			if ((prev_type == REDIR_IN || prev_type == REDIR_OUT
					|| prev_type == REDIR_APPEND || prev_type == REDIR_HEREDOC)
				&& (!tmp_token->token || ft_strlen(tmp_token->token) == 0))
			{
				// printf("minishell: %s: ambiguous redirect\n", tmp);
				// free(tmp);
				// ambig_redirect = 1;
				break ;
			}
		}
		prev_type = tmp_token->type;
		tmp_token = tmp_token->next;
	}
	if (ambig_redirect)
	{
		while (tmp_token && tmp_token->type != PIPE)
		{
			tmp_token = tmp_token->next;
		}
		if (tmp_token && tmp_token->type == PIPE)
		{
			tmp_token = tmp_token->next;
			ambig_redirect = 0;
		}
	}
	return (ambig_redirect);
}