/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/29 14:40:40 by zderfouf         ###   ########.fr       */
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
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(infile[i], 2);
			exit(1);
		}
		if (!infile[i + 1])
			if (dup2(fd, 0) == -1)
				error("dup2", 1337);
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
		if (!outfile[i + 1])
		{
			if (dup2(fd, 1) == -1) // fd & stdout_fd ===refers to===> file opene == -1)
				error("dup2", 1337);
		}
		close(fd); // close fd
		i++;
	}
}

void	aoutfile_opener(char **aoutfile)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (aoutfile && aoutfile[i])
	{
		fd = open(aoutfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("./minishell: no such file or directory: ", 2);
			ft_putendl_fd(aoutfile[i], 2);
			exit(1);
		}
		if (!aoutfile[i + 1])
			if (dup2(fd, 1) == -1) // fd & stdout_fd ===refers to===> file opene == -1)
				error("dup2", 1337);
		close(fd); // close fd
		i++;
	}
}

// void	outfiles(t_final	*lst)
// {
// 	int	i;
// 	int fd;

// 	i = 0;
// 	while (lst->aout_file[i] && lst->out_file[i])
// 	{
// 		if (lst->out_file[i])
// 			fd = open(lst->out_file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else
// 		 	fd = open(lst->aout_file[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			ft_putstr_fd("./minishell: no such file or directory: ", 2);
// 			ft_putendl_fd("SMIT LFILE", 2);
// 			exit(1);
// 		}
// 		i++;
// 	}
// }