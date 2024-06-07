/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/07 18:03:16 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_limiter(char *DELIMITER, int fd)
{
	char	*line;
	
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, DELIMITER, ft_strlen(DELIMITER)))
		{
			free (line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	heredoc_opener(char **heredoc)
{
	int		i;
	int		fd;

	i = 0;
	if (!heredoc)
		return ;
	while (heredoc[i])
		i++;
	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	heredoc_limiter(heredoc[i - 1], fd); // give the delimiter here
	close(fd);
	fd = open("/tmp/here_doc", O_RDONLY | O_CREAT, 0644);
	dup2(fd, 0);
	close(fd);
}

void	infile_opener(char **infile)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (infile && infile[i])
	{
		fd = open(infile[i], O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(infile[i], 2);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
		i++;
	}
}

void	outfile_opener(char **outfile)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (outfile && outfile[i])
	{
		fd = open(outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(outfile[i], 2);
			exit(1);
		}
		dup2(fd, 1); // fd & stdout_fd ===refers to===> file opened
		close(fd); // close fd
		i++;
	}
}

void	aoutfile_opener(char **outfile)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (outfile && outfile[i])
	{
		fd = open(outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(outfile[i], 2);
			exit(1);
		}
		dup2(fd, 1); // fd & stdout_fd ===refers to===> file opened
		close(fd); // close fd
		i++;
	}
}

