/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:54:48 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/07 17:51:50 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	else
		return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return (void) write(fd, "\n", 1);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write (fd, "\n", 1);
}

int	valid_check(char *str) // fix this
{
	int i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		write(2, "export: `", 9);
		ft_putstr_fd(str, 2);
		write(2, "': not a valide identifier\n", 27);
		return (0);
	}
	while (str[++i])
	{
		if (!(ft_isalpha(str[i]) || !(str[i] >= '0' && str[i] <= '9')))
		{
			write(2, "export: `", 9);
			ft_putstr_fd(str, 2);
			write(2, "': not a valide identifier\n", 27);
			return(0);
		}
	}
	return (1);
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