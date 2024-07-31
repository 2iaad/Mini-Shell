/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:14:26 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/31 15:43:38 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*name_heredoc(char *heredoc)
{
	char	*tmp;
	char	*num;
	char	*filename;

	(void)heredoc;
	tmp = gv_coll(1);
	if (!tmp)
		return (NULL);
	num = ft_itoa(*(int *)&tmp);
	filename = ft_strjoin("/tmp/.tmp", num);
	free(num);
	free(tmp);
	return (filename);
}

void	final_heredoc(t_file *files, int *flag)
{
	int	i;

	i = 0;
	while (files && files[i].type != 42)
	{
		if (files[i].type == DELIMITER)
			*flag = i;
		i++;
	}
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
