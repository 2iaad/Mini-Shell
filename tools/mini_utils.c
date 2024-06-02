/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:14:32 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/02 15:58:45 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void    ft_free(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}
void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int ft_strncmp(char *s1, char *s2, int len)
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

	if (ft_strncmp(s1, "-n", 1)) // if not real flag "-n"
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
