/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:16:25 by ibouram           #+#    #+#             */
/*   Updated: 2024/08/01 03:35:19 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_dollar_condition(char *line, int i, int len)
{
	return (line[i + len] == '$' && (
			(line[i + len + 1] == '\0' || line[i + len + 1] == ' '
				|| line[i + len + 1] == '\t'
				|| line[i + len + 1] == '+' || line[i + len + 1] == '=')
			|| (i + len - 1 >= 0 && i + len + 1 < ft_strlen(line)
				&& line[i + len - 1] == -2 && line[i + len + 1] == -2)
			|| (i + len - 1 >= 0 && i + len + 1 < ft_strlen(line)
				&& line[i + len - 1] == -1 && line[i + len + 1] == -1)
			|| (i + len - 1 >= 0 && i + len + 1 < ft_strlen(line)
				&& line[i + len - 1] == -2 && line[i + len + 1] == -1))
	);
}

void	expand_env_1(t_parse *pars, char *line, int i)
{
	pars->new_line = ft_substr(line, i, pars->len);
	pars->new = ft_strjoin_parse(pars->new, pars->new_line);
}

void	expand_env_2(t_parse *pars, int *i)
{
	pars->new = ft_strjoin_parse(pars->new, "$");
	*i += pars->len + 1;
}

void	handle_key_value(t_parse *ps, t_env *tmp_env, t_env **expander)
{
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, ps->new_line) == 0)
		{
			*expander = tmp_env;
			ps->new = ft_strjoin_parse(ps->new, (*expander)->value);
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

void	handle_dollar(t_parse *ps, char *line, t_env *env, t_env **expander)
{
	int		a;
	t_env	*tmp_env;

	ps->var_len = 1;
	while (line[ps->i + ps->len + ps->var_len]
		&& !delimiters(line[ps->i + ps->len + ps->var_len]))
		ps->var_len++;
	tmp_env = env;
	ps->new_line = ft_substr(line, ps->i + ps->len + 1, ps->var_len - 1);
	if (line[ps->i + ps->len + 1] == '?')
	{
		a = exit_status(0, 0);
		ps->new = ft_strjoin_parse(ps->new, ft_itoa(a));
		(ps->i)++;
	}
	else
		handle_key_value(ps, tmp_env, expander);
	ps->i += ps->len + ps->var_len;
}
