/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/12 16:56:16 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_expander(char **line, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(*line + 1, tmp->key, ft_strlen(*line)))
		{
			free(*line);
			*line = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	heredoc_limiter(char *DELIMITER, t_env *env, int fd)
{
	char	*line;
	
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '$' && line[1])
		{
			heredoc_expander(&line, env);
		}
		if (!ft_strncmp(line, DELIMITER, ft_strlen(DELIMITER)))
		{
			free (line);
			break ;
		}
		if (fd != 1337)
			ft_putendl_fd(line, fd);
		free(line);
	}
}

void	heredoc_opener(char **heredoc, t_env *env)
{
	int		i;
	int		fd;

	i = 0;
	if (!heredoc)
		return ;
	while (heredoc[i + 1])
	{
		heredoc_limiter(heredoc[i], env, 1337); // give the delimiter here
			i++;
	}
	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == 1)
		error("open", 1337);
	heredoc_limiter(heredoc[i], env, fd); // here heredoc[i] atkoun katpointi 3la akhir delimiter

	close(fd);
	fd = open("/tmp/here_doc", O_RDONLY | O_CREAT, 0644);
	if (dup2(fd, 0) == -1)
		error("open", 1337);
	close(fd);
}
