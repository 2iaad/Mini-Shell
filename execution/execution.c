/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:03:30 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/04 17:03:42 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*look_for_paths(char **ev)
{
	while (*ev)
	{
		if (ft_strnstr(*ev, "PATH=", ft_strlen(*ev)))
			return (*ev + ft_strlen("PATH="));
		ev++;
	}
	return (error("No path has been found.\n", 1), NULL);
}