/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/15 19:32:12 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			expand_herdoc(line, env);
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

void	reset_offset(char *filename, int fd)
{
	close(fd);
	fd = open(filename, O_RDONLY | O_CREAT, 0644);
	// if (unlink(filename) == -1)
	// 	error("unlink", 1337);
	if (fd == -1)
		error("open", 1337);
	close(fd);
}


void	heredoc_opener(t_file **files, t_env *env, int stdin_fd)
{
	int		i;
	int		flag;
	int		fd;
	char	*filename;

	i = 0;
	// printf("%s", (*files)[i].file);
	// exit(1);
	if (!file_checker(*files, DELIMITER))
		return ;
	i = 0;
	if (stdin_fd != 1337)
		if (dup2(stdin_fd, 0) == -1)
			error("dup2", 1337);
	while ((*files) && (*files)[i + 1].type != 42)
	{
		if ((*files)[i].type == DELIMITER)
			heredoc_limiter((*files)[i].file, env, 1337);
		i++;
	}
	filename = name_heredoc((*files)[i].file);
	
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("open", 1337);
	heredoc_limiter((*files)[i].file, env, fd); // here heredoc[i] atkoun katpointi 3la akhir delimiter
	close(fd);
	reset_offset(filename, fd);
	(*files)[i].file = filename;
	(*files)[i].type = IN_FILE;
}
