/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:49:39 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/04 16:13:05 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_mode(int mode, char c)
{
	if (c == '\'')
	{
		if (mode == 2)
			return (1);
		if (mode == 1)
			return (2);
	}
	else if (c == '\"')
	{
		if (mode == 3)
			return (1);
		if (mode == 1)
			return (3);
	}
	return (mode);
}

char	*enc_quotes(char *line)
{
	int		mode;
	char	*s;

	mode = 3;
	s = line;
	while (*s)
	{
		mode = switch_mode(mode, *s);
		if (*s == '"' && (mode == 3 || mode == 1))
			*s = -1;
		if (*s == '\'' && (mode == 2 || mode == 1))
			*s = -1;
		s++;
	}
	return (line);
}
