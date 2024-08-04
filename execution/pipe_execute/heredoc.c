/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 16:11:35 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	heredoc_signal(int tmp_fd, int fd)
{
	if (g_signal == 2)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
		close(fd);
		return (true);
	}
	return (false);
}

void	heredoc_limiter(char *DELIMITER, t_env *env, int fd, t_file *file)
{
	char	*line;
	int		tmp_fd;

	(1) && (tmp_fd = dup(0), rl_catch_signals = 1);
	signal(SIGINT, signal_handle_2);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (heredoc_signal(tmp_fd, fd))
			return ;
		if (!ft_strncmp(line, DELIMITER, ft_strlen(DELIMITER)))
		{
			free (line);
			break ;
		}
		if (file->flg == 0)
			line = expand_herdoc(line, env);
		if (fd != 1337)
			ft_putendl_fd(line, fd);
		free(line);
	}
	signal(SIGINT, signal_handle);
	return (rl_catch_signals = 0, dup2(tmp_fd, 0), (void)close(tmp_fd));
}

void	heredoc_maker(char **filename, char *DELIMITER, t_env *env, t_file *f)
{
	int		fd;

	*filename = name_heredoc(DELIMITER);
	fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("open", 1337);
	heredoc_limiter(DELIMITER, env, fd, f);
	reset_offset(*filename, fd);
}

void	heredoc_opener(t_file **files, t_env *env, int sec_fd)
{
	int		i;
	int		flag;
	char	*filename;

	i = 0;
	if (!file_checker(*files, DELIMITER))
		return ;
	if (dup2(sec_fd, 0) == -1)
		return (error("dup2", 1337));
	final_heredoc(*files, &flag);
	while ((*files) && (*files)[i].type != 42 && i < flag)
	{
		if ((*files)[i].type == DELIMITER)
			heredoc_limiter((*files)[i].file, env, 1337, &(*files)[i]);
		if (g_signal == 2)
			return ;
		i++;
	}
	heredoc_maker(&filename, (*files)[flag].file, env, &(*files)[i]);
	free((*files)[flag].file);
	(*files)[flag].file = filename;
	(*files)[flag].type = IN_FILE;
}
