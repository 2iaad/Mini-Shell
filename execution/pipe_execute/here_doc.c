/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:41 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 19:07:10 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_file_opener(int ac, char **av)
{
	int	fd;

	fd = open("/tmp/here_doc", O_RDONLY | O_CREAT, 0644);
	dup2(fd, 0);
	close(fd);
	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}

void	heredoc_limiter(char **av, int ac)
{
	char	*s;
	int		fd;

	if (ac < 6)
		error("retry with this: ./pipex here_doc LIMITER cmd cmd file", 1);
	fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "here_doc> ", 10);
		s = get_next_line(0);
		if (s == NULL)
			break ;
		if (ft_strncmp(s, av[2], ft_strlen(av[2])) == 0
			&& !(ft_strlen(av[2]) + 1 - ft_strlen(s)))
		{
			free (s);
			break ;
		}
		ft_putstr_fd(s, fd);
		free(s);
	}
	close(fd);
	heredoc_file_opener(ac, av);
}
