/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 06:33:48 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/09 06:33:36 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *word(char *line, int *i)
{
	char	*word;
	t_token	*node;
	int start;

	start = *i;
	while (line[*i] && !whitespaces(line[*i]))
		(*i)++;
	word = (char *)malloc(*i - start + 1);
	malloc_faill(word);
	while(start < *i)
	{
		word[start - *i] = line[start];
		start++;
	}
	word[start - *i] = '\0';
	node = ft_lstnew(word, WORD);
	malloc_faill(node);
	free(word);
	return (node);	
}

t_token *red_in_herdk(char *line, int *i)
{
	char	*redir;
	t_token	*node;

	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		redir = malloc(3);
		malloc_faill(redir);
		redir[0] = line[*i];
		redir[1] = line[*i + 1];
		redir[2] = '\0';
		(*i)++;
		node = ft_lstnew(redir, REDIR_HEREDOC);
	}
	else
	{
		redir = malloc(2);
		malloc_faill(redir);
		redir[0] = line[*i];
		redir[1] = '\0';
		(*i)++;
		node = ft_lstnew(redir, REDIR_IN);
	}
	malloc_faill(node);
	free(redir);
	return (node);
}

t_token *red_out_apnd(char *line, int *i)
{
	char	*redir;
	t_token	*node;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		redir = malloc(3);
		malloc_faill(redir);
		redir[0] = line[*i];
		redir[1] = line[*i + 1];
		redir[2] = '\0';
		(*i)++;
		node = ft_lstnew(redir, REDIR_APPEND);
	}
	else
	{
		redir = malloc(2);
		malloc_faill(redir);
		redir[0] = line[*i];
		redir[1] = '\0';
		(*i)++;
		node = ft_lstnew(redir, REDIR_OUT);
	}
	malloc_faill(node);
	free(redir);
	return (node);
}


t_token *ft_pipe(char *line, int *i)
{
	char	*pipe;
	t_token	*node;

	pipe = (char *)malloc(2);
	pipe[0] = line[*i];
	pipe[1] = '\0'; 
	(*i)++;
	node = ft_lstnew(pipe, PIPE);
	malloc_faill(node);
	free(pipe);
	return (node);
}

void	tokenizer(char *line, t_token **token)
{
	int	i;
	t_token *node;

	i = 0;
	while (line[i])
	{
		if (i == 0 || whitespaces(line[i]))
		{
			while (line[i] && whitespaces(line[i]))
				i++;
			if (line[i] != '|' && line[i] != '<' && line[i] != '>')
				node = word(line, &i);
			else if (line[i] == '|')
				node = ft_pipe(line, &i);
			else if (line[i] == '<')
				node = red_in_herdk(line, &i);
			else if (line[i] == '>')
				node = red_out_apnd(line, &i);
			if (node->token != NULL)
				ft_lstadd_back(&token, node);
			else
				i++;
		}
	}
}
