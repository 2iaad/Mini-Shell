// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   file_opener.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
// /*   Updated: 2024/07/15 10:35:01 by zderfouf         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../minishell.h"

void	in(t_file *files)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (files && files[i].type != 42)
	{
		if (files[i].type == IN_FILE)
		{

			fd = open(files[i].file, O_RDONLY, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("./minishell: no such file or directory: ", 2);
				ft_putendl_fd(files[i].file, 2);
				exit(1);
			}
			if (files[i].last == true)
				if (dup2(fd, 0) == -1)
					error("dup2", 1337);
			close(fd);
		}
		i++;
	}
}

void	out(t_file *files)
{
	int i;
	int	fd;

	i = 0;
	fd = 0;
	while (files && files[i].type != 42)
	{
		if (files[i].type == OUT_FILE || files[i].type == AOUT_FILE)
		{
			if (files[i].type == OUT_FILE)
				fd = open(files[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (files[i].type == AOUT_FILE)
				fd = open(files[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("./minishell: no such file or directory: ", 2);
				ft_putendl_fd(files[i].file, 2);
				exit(1);
			}
			if (files[i].last == true)
				if (dup2(fd, 1) == -1)
					error("dup22222", 1337);
			close(fd);
		}
		i++;
	}
}
