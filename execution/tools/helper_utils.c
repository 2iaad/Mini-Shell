/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:54:48 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/03 18:39:15 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalpha(int c)
{
	if (c == '_' || (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ((void) write(fd, "\n", 1));
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write (fd, "\n", 1);
}

long	ft_atol(char *str)
{
	int		i;
	int		s;
	long	nb;

	i = 0;
	s = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb * s > INT_MAX)
			return (LONG_MAX);
		else if (nb * s < INT_MIN)
			return (LONG_MIN);
		i++;
	}
	return (nb * s);
}

bool	add_pwd(t_env **env)
{
	char *value;
	char *s;

	value  = getcwd(NULL, -1337);
	if (!value)
		return (perror("getcwd"), exit_status(1, 1), true);
	s = ft_strdup(value);
	free(value);
	ft_lstadd_back(env, ft_lstnew(ft_strdup("PWD"), s));
	return (false);
}