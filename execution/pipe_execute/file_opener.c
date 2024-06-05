/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/05 11:34:15 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	infile_opener(char **infile)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (infile && infile[i])
	{
		fd = open(infile[i], O_RDONLY, 0644);
		dup2(fd, 0);
		close(fd);
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(infile[i], 2);
			exit(1);
		}
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
		dup2(fd, 1);
		close(fd);
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(outfile[i], 2);
			exit(1);
		}
		i++;
	}
}