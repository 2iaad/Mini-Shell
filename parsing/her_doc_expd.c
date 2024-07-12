/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_expd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:52:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/11 18:11:10 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// when $and not in env ==> should return ambiguous redirect (this fo in file and outfile and append)
// if << '"ss"' ==> should not expand the variable (if there quotes)

char	*expand_herdoc(char *line, t_env *env)
{
    int 	i;
    int		len;
    char	*new_line;
    char	*new;
    t_env	*tmp_env;
    t_env	*expander;
    int		var_len;

    i = 0;
    new = NULL;
    expander = NULL;
    while (line[i])
    {
        len = 0;
        while (!(line[i + len] == '$') && line[i + len] != '\0')
            len++;
        if (len > 0) // if there is a string before the variable
        {
            new_line = ft_substr(line, i, len);
            new = ft_strjoin_parse(new, new_line);
        }
        if (line[i + len] == '$' && (line[i + len + 1] == '\0' || line[i + len + 1] == ' '))
        {
            new = ft_strjoin_parse(new, "$");
            i += len + 1;
        }
        else if (line[i + len] == '$' && ft_isnum(line[i + len + 1]))
        {
            var_len = 1;
            while(line[i + len + var_len] && ft_isnum(line[i + len + var_len]))
                var_len++;
            new_line = ft_substr(line, i + len + 2, var_len - 2);
            new = ft_strjoin_parse(new, new_line);
            i += len + var_len;
        }
        else if (line[i + len] == '$')
        {
            var_len = 1;
            while(line[i + len + var_len] && !delimiters(line[i + len + var_len]))
                var_len++;
            tmp_env = env;
            new_line = ft_substr(line, i + len + 1, var_len - 1);
            while (tmp_env)
            {
                if (ft_strcmp(tmp_env->key, new_line) == 0)
                {
                    expander = tmp_env;
                    new = ft_strjoin_parse(new, expander->value);
                    break ;
                }
                tmp_env = tmp_env->next;
            }
            i += len + var_len;
        }
        else
            i += len;
    }
    return (new);
}


void	read_herdoc(t_token *token)
{
    while (token != NULL)
    {
        if (token->type == DELIMITER)
        {
			if (check_quotes(token->token))
				token->flg = 1;
			else
                token->flg = 0;
		}
        token = token->next;
    }
}
// another tehnique is to use a flag to check if the delimiter is enclosed in quotes
// if it is, then we don't expand the variables inside the heredoc
// so we got to expand if flg = 1 we expand if flg = 0 we don't expand