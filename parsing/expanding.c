/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 03:47:44 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/21 05:39:09 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_env(char *line, t_env *env)
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
		while (!(line[i + len] == '$' && valid_meta2(line, i + len, 0, 1)) && line[i + len] != '\0')
			len++;
		if (len > 0) // if there is a string before the variable
		{
			new_line = ft_substr(line, i, len);
			new = ft_strjoin_parse(new, new_line);
		}
		if (line[i + len] == '$' && (line[i + len + 1] == '\0' || line[i + len + 1] == ' '
			|| line[i + len + 1] == '\'' || line[i + len + 1] == '\"'))
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

void expanding(t_token *token, t_env *env)
{
    t_token *tmp_token;
    char *tmp;
	char **split;
    int prev_type = -1;  // Initialize with an invalid type
    int ambig_redirect = 0;  // Flag for ambiguous redirect

    tmp_token = token;
    while (tmp_token && !ambig_redirect)
    {
        if (tmp_token->type != REDIR_IN && tmp_token->type != REDIR_OUT
            && tmp_token->type != REDIR_APPEND && tmp_token->type != REDIR_HEREDOC
            && tmp_token->type != DELIMITER)
        {
            tmp = tmp_token->token;
            tmp_token->token = expand_env(tmp_token->token, env);
            if ((prev_type == REDIR_IN || prev_type == REDIR_OUT || prev_type == REDIR_APPEND || prev_type == REDIR_HEREDOC) && (!tmp_token->token || ft_strlen(tmp_token->token) == 0))
            {
                printf("minishell: %s: ambiguous redirect\n", tmp);
                free(tmp);
                ambig_redirect = 1;
                break;
            }
        }
        prev_type = tmp_token->type;
        tmp_token = tmp_token->next;
    }

    if (ambig_redirect)
    {
        while (tmp_token)
        {
            tmp = tmp_token->token;
            tmp_token->token = NULL;
            free(tmp);
            tmp_token = tmp_token->next;
        }
    }
}

