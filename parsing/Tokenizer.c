/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 06:33:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/23 02:45:58 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_get_token(char *content, int type)
{
	t_token	*n;

	n = (t_token *)malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	n->token = ft_strdup(content);
	n->type = type;
	n->next = NULL;
	return (n);
}

void	tokenizer_1(char **splited, t_token **token)
{
    int	i;
    t_token *node;

    node = NULL;
    (void)token;
    i = 0;
    if (!splited)
        return ;
    while (splited[i])
    {
        if (ft_strcmp(splited[i], "|") == 0)
            node = ft_get_token("|", PIPE);
        else if (ft_strcmp(splited[i], "<") == 0)
            node = ft_get_token("<", REDIR_IN);
        else if (ft_strcmp(splited[i], ">") == 0)
            node = ft_get_token(">", REDIR_OUT);
        else if (ft_strcmp(splited[i], ">>") == 0)
            node = ft_get_token(">>", REDIR_APPEND);
        else if (ft_strcmp(splited[i], "<<") == 0)
            node = ft_get_token("<<", REDIR_HEREDOC);
		else
            node = ft_get_token(splited[i], WORD);
        if (node != NULL && node->token != NULL)
            ft_lstadd_back_parse(token, node);
        i++;
    }
}

void	tokenizer_2(t_token **token)
{
	t_token *node;

	node = *token;
	while (node)
	{
		if (node->next)
		{
			if (node->type == REDIR_IN)
				node->next->type = IN_FILE;
			else if (node->type == REDIR_OUT)
				node->next->type = OUT_FILE;
			else if (node->type == REDIR_APPEND)
				node->next->type = AOUT_FILE;
			else if (node->type == REDIR_HEREDOC)
				node->next->type = DELIMITER;
		}
		node = node->next;
	}
}

void    tokenizer_3(t_token **token)
{
    t_token *node;
    int     cmd_found;

    node = *token;
    while (node)
    {
        if (node == *token || node->type == PIPE)
        {
			if (node->type == PIPE)
				node = node->next;
            cmd_found = 0;
            while (node && node->type != PIPE)
            {
				if (node->token == NULL)
				{
					node = node->next;
					continue ;
				}
                if (node->type == WORD)
                {
                    if (cmd_found == 0)
                    {
                        node->type = CMD;
                        cmd_found = 1;
                    }
                    else
                        node->type = OPTION;
                }
				node = node->next;
            }
        }
		else
			node = node->next;
    }
}

void    replace_quotes(t_token **token)
{
    t_token *node;
    int     i;

    node = *token;
    while (node)
    {
        i = 0;
        while (node->token[i])
        {
            if (node->token[i] == '\'')
                node->token[i] = -1;
            else if (node->token[i] == '\"')
                node->token[i] = -2;
            i++;
        }
        node = node->next;   
    }
}

void   tokenizer(char **splited, t_token **token, t_env *env)
{
    tokenizer_1(splited, token);
    tokenizer_2(token);
    replace_quotes(token);
	int ambg_redir = expanding(*token, env);
    if (ambg_redir)
        return ;
	tokenizer_3(token);
}
// remove quotes
// split by pipe
