/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:14:32 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/03 20:29:17 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/tools.h"

void    ft_free(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_putstr(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        write(1, &str[i], 1);
}

int ft_strcmp(char *s1, char *s2, int len)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i] && i < len)
        i++;
    return(s1[i] - s2[i]);
}

int flag_check(char *s1) // check if s1 == "-n" or -nnnnnnn
{
    int i;

	if (ft_strcmp(s1, "-n", 1)) // if not real flag "-n"
		return (1);
    i = 2;
	while (s1[i]) // if not real flag "-nnnnx"
	{
		if (s1[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
