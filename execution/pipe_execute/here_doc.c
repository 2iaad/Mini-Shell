/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/11 15:17:17 by ibouram          ###   ########.fr       */
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
	t_file	*file;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line[0] == '$' && line[1] && file->flg == 0)
			expand_herdoc(&line, env);
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

char	*name_heredoc(char *heredoc)
{
	char	*tmp;
	char	*num;
	char	*filename;
	
	tmp = ft_strjoin("/tmp/.", heredoc);
	num = ft_itoa(*(int *)&tmp);
	filename = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	return (filename);
}

void	reset_offset(char **filename, int fd)
{
	close(fd);
	fd = open(*filename, O_RDONLY | O_CREAT, 0644);
	if (unlink(*filename) == -1)
		error("unlink", 1337);
	free(*filename);
	if (fd == -1)
		error("open", 1337);
	if (dup2(fd, 0) == -1)
		error("open", 1337);
	close(fd);
}

void	heredoc_opener(char **heredoc, t_env *env, int stdin_fd)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	if (stdin_fd != 1337)
		if (dup2(stdin_fd, 0) == -1)
			error("dup2", 1337);
	while (heredoc[i + 1])
	{
		heredoc_limiter(heredoc[i], env, 1337); // give the delimiter here
			i++;
	}
	filename = name_heredoc(heredoc[i]);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("open", 1337);
	heredoc_limiter(heredoc[i], env, fd); // here heredoc[i] atkoun katpointi 3la akhir delimiter
	reset_offset(&filename, fd);
}
