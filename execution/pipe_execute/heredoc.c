/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/25 17:52:35 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_limiter(char *DELIMITER, t_env *env, int fd, t_file *file)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = dup(0);
	signal(SIGINT, signal_handle_2);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (file->flg == 0)
			line = expand_herdoc(line, env);
		if (!ft_strncmp(line, DELIMITER, ft_strlen(DELIMITER)))
		{
			free (line);
			break ;
		}
		if (fd != 1337)
			ft_putendl_fd(line, fd);
		free(line);
	}
	signal(SIGINT, signal_handle);
	dup2(tmp_fd, 0);
	close(tmp_fd);
}

void	heredoc_maker(char **filename, char *DELIMITER, t_env *env, t_file *f)
{
	int		fd;
	
	*filename = name_heredoc(DELIMITER);
	fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("open", 1337);
	heredoc_limiter(DELIMITER, env, fd, f); // here heredoc[i] atkoun katpointi 3la akhir delimiter
	reset_offset(*filename, fd);
}

void	heredoc_opener(t_file **files, t_env *env, int stdin_fd)
{
	int		i;
	int		flag;
	char	*filename;

	i = 0;
	if (!file_checker(*files, DELIMITER))
		return ;
	if (dup2(stdin_fd, 0) == -1)
		error("dup2", 1337);
	final_heredoc(*files, &flag); // kanflagi last heredoc
	while ((*files) && (*files)[i].type != 42 && i < flag) // kanreadi 7tal akhir heredoc
	{
		if ((*files)[i].type == DELIMITER)
			heredoc_limiter((*files)[i].file, env, 1337, &(*files)[i]); // kanopeni heredoc
		i++;
	}
	heredoc_maker(&filename, (*files)[flag].file, env, &(*files)[i]); // last one anopenih
	(*files)[flag].file = filename; // nrdo IN_FILE bash nopenin f in() function
	(*files)[flag].type = IN_FILE;
}
