/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:12:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 16:04:56 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>


// $a $hddhd -l

typedef struct s_env
{
	char			*key;
    char			*value;
    struct s_env	*next;
}   t_env;

typedef struct s_list
{
	char	**cmd;
	t_env	*env;
}	t_list;

/*          BUILTINS        */

void    echo(t_list	*lst);
void    cd(t_list *lst);
void    pwd(void);
void    env(t_list *cmd);
void	unset(t_list	*lst);
void	export_command(t_list *lst);
void	exit_command(char **cmd);

/*          EXECUTION       */

void	ft_free(char **tab);
void	error(char *str, int a);
char	*look_for_paths(char **env);
void	pipex(char *cmd, char **env);
void	first_child(char **av, char **ev);
void	heredoc_limiter(char **av, int ac);
char	*right_path(char *cmd, char **env);
void	execute_cmd(char *cmd, char **env);
void	heredoc_file_opener(int ac, char **av);
int		normal_file_opener(int a, char *file);

/*			TOOLS			*/

int		ft_isalpha(int c);
int		valid_check(char *str);
void    ft_free(char **str);
int     flag_check(char *s1);
char	*ft_strdup(char *s1);
int     ft_strlen(char *str);
long	ft_atol(char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
int     ft_strncmp(char *s1, char *s2, int len);
char	**custumized_ft_split(const char *str, char c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);

		//			 linked list
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstadd_back(t_env **lst, t_env *newn);

#endif