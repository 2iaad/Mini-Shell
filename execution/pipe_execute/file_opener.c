/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 17:00:28 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	in(char *infile, bool last)
{
	int	fd;

	fd = open(infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("./minishell: no such file or directory: ", 2);
		ft_putendl_fd(infile, 2);
		exit(1);
	}
	if (last == true)
		if (dup2(fd, 0) == -1)
			error("dup2", 1337);
	close(fd);
}

void	out(char *outfile, int type, bool last)
{
	int	fd;

	if (type == OUT_FILE)
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == AOUT_FILE)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error("open", 1337);
	if (last == true)
		if (dup2(fd, 1) == -1)
			error("dup2", 1337);
	close(fd);
}

void	file_opener(t_file *files)
{
	int	i;
	int	fd;

	(1 == 1) && ((i = 0) && (fd = 0));
	while (files && files[i].type != 42)
	{
		if (files[i].file == NULL)
			return (ambious_redirect(files[i].file), exit(1));
		if (files[i].type == OUT_FILE || files[i].type == AOUT_FILE)
			out(files[i].file, files[i].type, files[i].last);
		else if (files[i].type == IN_FILE)
			in(files[i].file, files[i].last);
		i++;
	}
}
