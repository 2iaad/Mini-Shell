/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_expd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:52:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/31 16:10:20 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_numr(t_pars *pars, char *line, int *i)
{
	pars->var_len = 1;
	while (line[*i + pars->len + pars->var_len]
		&& ft_isnum(line[*i + pars->len + pars->var_len]))
		pars->var_len++;
	pars->new_line = ft_substr(line, *i + pars->len + 2, pars->var_len - 2);
	pars->new = ft_strjoin_parse(pars->new, pars->new_line);
	*i += pars->len + pars->var_len;
}

void	handle_value(t_args *args)
{
	t_env	*tmp_env;

	args->pars->var_len = 1;
	while (args->line[*args->i + args->pars->len + args->pars->var_len]
		&& !delimiters(args->line[*args->i
				+ args->pars->len + args->pars->var_len]))
		args->pars->var_len++;
	tmp_env = args->env;
	args->pars->new_line = ft_substr(args->line, *args->i
			+ args->pars->len + 1, args->pars->var_len - 1);
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, args->pars->new_line) == 0)
		{
			*args->expander = tmp_env;
			args->pars->new = ft_strjoin_parse(args->pars->new,
					(*args->expander)->value);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	*args->i += args->pars->len + args->pars->var_len;
}

void	handl_dollar(t_pars *pars, char *line, t_env *env, t_env **expander)
{
	t_args	args;

	args.pars = pars;
	args.line = line;
	args.i = &pars->i;
	args.env = env;
	args.expander = expander;
	if (line[pars->i + pars->len] == '$'
		&& (line[pars->i + pars->len + 1] == '\0'
			|| line[pars->i + pars->len + 1] == ' '
			|| line[pars->i + pars->len + 1] == '\''
			|| line[pars->i + pars->len + 1] == '\"'))
	{
		pars->new = ft_strjoin_parse(pars->new, "$");
		pars->i += pars->len + 1;
	}
	else if (line[pars->i + pars->len] == '$'
		&& ft_isnum(line[pars->i + pars->len + 1]))
		handle_numr(pars, line, &pars->i);
	else if (line[pars->i + pars->len] == '$')
		handle_value(&args);
	else
		pars->i += pars->len;
}

char	*expand_herdoc(char *line, t_env *env)
{
	t_pars	pars;
	t_env	*expander;

	pars.i = 0;
	pars.new = NULL;
	expander = NULL;
	while (line[pars.i])
	{
		pars.len = 0;
		while (!(line[pars.i + pars.len] == '$')
			&& line[pars.i + pars.len] != '\0')
			pars.len++;
		if (pars.len > 0)
		{
			pars.new_line = ft_substr(line, pars.i, pars.len);
			pars.new = ft_strjoin_parse(pars.new, pars.new_line);
		}
		handl_dollar(&pars, line, env, &expander);
	}
	if (!pars.new)
		return (line);
	else
	 	free(line);
	return (pars.new);
}

void	read_herdoc(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == DELIMITER && token->token != NULL)
		{
			if (ft_strchr(token->token, -1) || ft_strchr(token->token, -2))
				token->flg = 1;
			else
				token->flg = 0;
		}
		token = token->next;
	}
}
