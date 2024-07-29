/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:56:15 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/29 09:47:48 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	s_in(char *infile, bool last)
{
	int	fd;

	if (g_signal == 2)
		return (false);
	fd = open(infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("./minishell: no such file or directory: ", 2);
		ft_putendl_fd(infile, 2);
		return (false);
	}
	if (last == true)
		if (dup2(fd, 0) == -1)
			error("dup2", 1337);
	close(fd);
	return (true);
}

bool	s_out(char *outfile, int type, bool last)
{
	int	fd;

	if (type == OUT_FILE)
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == AOUT_FILE)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), false);
	if (last == true)
		if (dup2(fd, 1) == -1)
			error("dup2", 1337);
	close(fd);
	return (true);
}

bool	s_file_opener(t_file *files)
{
	int		i;
	bool	flag[2];

	i = 0;
	flag[0] = true;
	flag[1] = true;
	if (g_signal == 2)
		return (false);
	while (files && files[i].type != 42)
	{
		if (files[i].type == IN_FILE)
			flag[0] = s_in(files[i].file, files[i].last);
		else if (files[i].type == OUT_FILE || files[i].type == AOUT_FILE)
			flag[1] = s_out(files[i].file, files[i].type, files[i].last);
		if (!flag[0] || !flag[1])
			return (false);
		i++;
	}
	return (true);
}
