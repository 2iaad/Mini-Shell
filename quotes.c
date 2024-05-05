/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:10 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/05 20:30:01 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line)
{
	int	i;
	int	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}