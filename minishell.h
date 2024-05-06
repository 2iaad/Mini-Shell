/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:45:46 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/06 19:04:15 by ibouram          ###   ########.fr       */
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



char	**ft_split(const char *s, char *sub_s);
void	read_from_input(t_env **env);
int		parce_line(char *line, t_env **env);
int		check_quotes(char *line);
int		whitespaces(char s);
void	space(char *line);
int 	ft_strlen(char *s);
#endif