/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:45:46 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/31 03:24:26 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

/* 

	gv_coll
	norm
	"$HOME"$"$HOME"
	ls > $dd | ls 
	ctrl + c in heredoc
*/

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}				t_garbage;

typedef struct s_herdc
{
	char	*line;
	int		*i;
}				t_herdc;

typedef struct s_pars
{
	char	*new_line;
	char	*new;
	int		var_len;
	int		len;
	int		i;
}				t_pars;

typedef struct s_parse
{
	char	*new_line;
	char	*new;
	int		var_len;
	int		len;
	int		i;
}				t_parse;

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}				t_free;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*token;
	int				type;
	int				index;
	int				flg;
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
	AOUT_FILE,
	DELIMITER
}	t_meta;

typedef struct s_file
{
	char	*file;
	int		type;
	int		flg;
	bool	last;
}				t_file;

typedef struct s_final
{
	char			*cmd;
	char			**args;
	char			**final_cmd;
	t_file			*files;
	struct s_final	*next;
}					t_final;

typedef struct s_args
{
	t_pars	*pars;
	char	*line;
	int		*i;
	t_env	*env;
	t_env	**expander;
}	t_args;

int		g_signal;

//*----------------------------------TOOLS------------------------------------------*//
//*---Parsing---*
char	**split_line(char *line);
int		ft_strlen(char *s);
int		whitespaces(char s);
void	ft_putstr_fd(char *s, int fd);
int		ft_isalnum(int c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *s1);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsiz);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_parse(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
//*//*---Execution---*
int		ft_isalpha(int c);
int		ft_isnum(int c);
int		export_valid_check(char *str, t_env ***env);
int		unset_valid_check(char *str, t_env ***env);
void	ft_free(char **str);
int		flag_check(char *s1);
long	ft_atol(char *str);
char	*ft_itoa(int n);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
int		ft_strncmp(char *s1, char *s2, int len);
char	**custumized_ft_split(const char *str, char c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
void	signal_handle(int sig);

//*----------------------------------linked_list------------------------------------------*//
//*---Parsing---*
t_token	*ft_lstnew_parse(char *content, int type);
t_token	*ft_lstlast_parse(t_token *lst);
t_env	*ft_lstlast2_parse(t_env *lst);
void	ft_lstadd_back_parse(t_token **lst, t_token *new);
void	ft_lstadd_back_2_parse(t_env **lst, t_env *new);
void	ft_lstadd_back3_parse(t_final **lst, t_final *new);
t_final	*ft_lstlast3_parse(t_final *lst);
//*---Execution---*
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstadd_back(t_env **lst, t_env *newn);

//*----------------------------------PARSING--------------------------------------------------------------*//

void	read_from_input(t_final *final_cmd, t_env **env_list, char **envp);
int		parce_line(t_final **final_cmd, t_env *env, char *line);
void	init_signals(void);
void	signal_handle_2(int sig);

//*----------------------CHECK_QOUTES-----------------------------*//

int		check_quotes(char *line);
int		valid_meta(char *line, int i, int j, int valid);
int		vm2(char *line, int i, int j, int valid);

//*----------------------REMOVE_QOUTES---------------------------*//

void	token_quotes(t_token **token);
char	*remove_quotes(char *line);

//*----------------------ADD_SPACE--------------------------*//

int		space_len(char *line, int i);
char	*space(char *line, int i, int j);
void	spaces_sing_quot(char *new_line, char *line, int *j, int i);
void	spaces_doubl_quot(char *new_line, char *line, int *j, int i);
char	*trim_line(char *line);

//*----------------------EXPANDING---------------------------*//

int		delimiters(char c);
char	*expand_env(char *line, t_env *env);
void	handle_dollar(t_parse *pars, char *line, t_env *env, t_env **expander);
void	expand_env_2(t_parse *pars, int *i);
void	expand_env_1(t_parse *pars, char *line, int i);
char	*handle_num(char *line, int *i);
bool	check_dollar_condition(char *line, int i, int len);
int		expanding(t_token *token, t_env *env);
char	*expand_herdoc(char *line, t_env *env);
void	read_herdoc(t_token *token);

//*----------------------SYNTAX_ERROR---------------------------*//

int		syntax_error(t_token *token);

//*----------------------TOKENIZER---------------------------*//

int		tokenizer(char **splited, t_token **token, t_env *env);
t_token	*ft_get_token(char *content, int type);
void	replace_quotes(t_token **token);
void	tokenizer_3(t_token **token);
void	process_node(t_token **node, int *cmd_found);
void	tokenizer_2(t_token **token);
void	tokenizer_1(char **splited, t_token **token);
t_token	*ft_get_token(char *content, int type);

//*----------------------STRUCT---------------------------*//

t_final	*struct_init(t_token **token);
t_final	*init_final(t_token **nodee);
int		count_len(t_token *node, int type);
void	post_process_files(t_final **tmp, int files_index);

// *------------------------------------------------------------------------------------------------------------------------------------------*//

// *--------------------------------------EXECUTION----------------------------------------------------* //

//*---------------------BUILTINS--------------------------*//

// void	merg_cmd(t_final	***lst);

bool	builtins(t_final *lst, t_env **env_list);
void	execution(t_final *lst, t_env **env, struct termios *p);
void	echo(t_final	*lst);
void	cd(t_final	*lst, t_env *env);
void	pwd(void);
void	env(t_env *env_list);
void	unset(t_final	*lst, t_env **env_list);
void	export_command(t_final *lst, t_env **env_list);
void	exit_command(char **cmd);

//*---------------------EXECUTION--------------------------*//

void	init_env(t_env **env_list, char **env);
char	*right_path(char **cmd, char **env);
char	*look_for_paths(char **ev);

bool	file_checker(t_file *files, int type);
void	parce_files(t_final **lst);

char	*name_heredoc(char *heredoc);
void	final_heredoc(t_file *files, int *flag);
void	reset_offset(char *filename, int fd);
void	heredoc_opener(t_file **files, t_env *env, int stdin_fd);

void	in(char *infile, bool last);
void	out(char *outfile, int type, bool last);
bool	file_opener(t_file *files);
bool	s_in(char *infile, bool last);
bool	s_out(char *outfile, int type, bool last);
bool	s_file_opener(t_file *files);
void	init_secfds(int *sec_fd, int flag);
void	multiple_helper(t_env **env);

void	pipe_cmd(t_final *lst, int *fds, int flag);
void	child(t_final *lst, t_env **env, int *fds);
void	execute_cmd(t_final	*lst, t_env *envp);

void	env_maker(t_env *envp, char ***env);
void	env_copy(t_env **env_list, t_env **copy);
void	alpha_arrang(t_env *env);
void	export_solo(t_env *env);
void	export_replace(t_env *env, char **str);
void	export_var(t_env *env, char **str);
void	export_join(t_env *env, char **str);
void	error(char *str, int a);
int		exit_status(int status, int set);

//*---------------------Garbage Collector--------------------------*//

void	*gv_coll(size_t size);
void	add_to_gc(void *addr);

#endif