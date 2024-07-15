/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:55:06 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/15 19:35:07 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool file_checker(t_file *files, int type)
{
	int i;

	i = 0;
	while (files && files[i].type != 42)
	{
		if (files[i].type == type)
			return (true);
		i++;
	}
	return (false);
}

void	init_l_files(char **l_in, char **l_out, t_file *files)
{
	int	i;

	i = 0;
	while (files && files[i].type != 42)
	{
		if (files[i].type == IN_FILE)
			*l_in = files[i].file;
		else if (files[i].type == DELIMITER)
			*l_in = files[i].file;
		else if (files[i].type == OUT_FILE)
			*l_out = files[i].file;
		else if (files[i].type == AOUT_FILE)
			*l_out = files[i].file;
		i++;
	}
}

void	parce_files(t_file **files)
{
	int		i;
	char	*l_in;
	char	*l_out;

	i = 0;
	init_l_files(&l_in, &l_out, *files);
	while ((*files) && (*files)[i].type != 42)
	{
		if ((*files)[i].type == IN_FILE && (*files)[i].file == l_in)
			(*files)[i].last = true;
		else if ((*files)[i].type == OUT_FILE && (*files)[i].file == l_out)
			(*files)[i].last = true;
		else if ((*files)[i].type == AOUT_FILE && (*files)[i].file == l_out)
			(*files)[i].last = true;
		else if ((*files)[i].type == DELIMITER && (*files)[i].file == l_in)
			(*files)[i].last = true;
		else
			(*files)[i].last = false;
		i++;
	}
}