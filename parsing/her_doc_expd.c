/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_expd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:52:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/27 19:51:59 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        if (len > 0)
        {
            new_line = ft_substr(line, i, len);
            new = ft_strjoin_parse(new, new_line);
        }
        if (line[i + len] == '$' && (line[i + len + 1] == '\0'
            || line[i + len + 1] == ' ' || line[i + len + 1] == '\'' || line[i + len + 1] == '\"'))
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
	if (!new)
		return (line);
    return (new);
}


void	read_herdoc(t_token *token)
{
    while (token != NULL)
    {
        if (token->type == DELIMITER)
        { 
			if (ft_strchr(token->token, -1) || ft_strchr(token->token, -2))
            {
				token->flg = 1;
            }
			else
            {
                token->flg = 0;
            }
		}
        token = token->next;
    }
}
