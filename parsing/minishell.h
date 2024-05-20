/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:45:46 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/20 10:21:14 by ibouram          ###   ########.fr       */
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
	char			*variable;
	char			*value;
	struct s_env	*next;
}					t_env;

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
	CMD,
	OPTION,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND_FILE,
	HEREDOC_FILE
} t_meta;

char	**ft_split(const char *s, char *sub_s);
char	**split_line(char *line);
void	read_from_input(t_env **env);
int		parce_line(char *line, t_env **env);
int		check_quotes(char *line);
int		whitespaces(char s);
int		is_word(char *str);
int 	ft_strlen(char *s);
int		valid_meta(char *line, int i, int j, int valid);
int		valid_meta2(char *line, int i, int j, int valid);
int		space_len(char *line, int i);
char	*space(char *line, int i, int j);
void	spaces_sing_quot(char *new_line, char *line, int *j, int i);
void	spaces_doubl_quot(char *new_line, char *line, int *j, int i);
t_token	*ft_lstnew(char *content, int type);
t_token	*ft_lstlast(t_token *lst);
t_env	*ft_lstlast2(t_env *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_back_2(t_env **lst, t_env *new);
t_token *word(char *line, int *i);
t_token *red_in_herdk(char *line, int *i);
t_token *red_out_apnd(char *line, int *i);
t_token *ft_pipe(char *line, int *i);
void	ft_putstr_fd(char *s, int fd);
int		ft_isalnum(int c);
int		ft_isnum(int n);
int 	delimiters(char c);
char	*parse_protec(char *line);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsiz);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		is_operator(char *line, int *i);
void	skip_spaces(char *line, int *i, int inc);
int		syntax_error(char *line);
t_env	*get_env(char **envp);
int		ft_strcmp(char *s1, char *s2);
char	*expand_env(char *line, t_env **env);
char	*trim_line(char *line);
void	tokenizer(char **splited, t_token **token);
int		is_oper(char *tok, int asc, int len);
#endif