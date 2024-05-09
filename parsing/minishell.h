/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:45:46 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/09 06:23:40 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

typedef struct s_env
{
	char	*variable;
	int		*value;
}				t_env;

typedef struct s_token
{
	char	*token;
	int		type;
	int		index;
	struct s_token	*next;
}				t_token;

typedef enum s_meta
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
} t_meta;

char	**ft_split(const char *s, char *sub_s);
void	read_from_input(t_env **env);
int		parce_line(char *line, t_env **env);
int		check_quotes(char *line);
int		whitespaces(char s);
int 	ft_strlen(char *s);
int		valid_meta(char *line, int i, int j, int valid);
int		space_len(char *line, int i, int j);
char	*space(char *line, int i, int j);
void	spaces_sing_quot(char *new_line, char *line, int *j, int i);
void	spaces_doubl_quot(char *new_line, char *line, int *j, int i);
t_token	*ft_lstnew(char *content, int type);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	malloc_faill(char *buffer);
t_token *word(char *line, int *i);
t_token *red_in_herdk(char *line, int *i);
t_token *red_out_apnd(char *line, int *i);
t_token *ft_pipe(char *line, int *i);
#endif