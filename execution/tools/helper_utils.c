/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:54:48 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/21 06:23:44 by zderfouf         ###   ########.fr       */
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
		return (void) write(fd, "\n", 1);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write (fd, "\n", 1);
}

void	export_error(char *str)
{
		write(2, "export: `", 9);
		ft_putstr_fd(str, 2);
		write(2, "': not a valide identifier\n", 27);
}
int	valid_check(char *str, t_env ***env)
{
	int i;

	i = 0;
	if (!(ft_isalpha(str[0])))
		return (export_error(str), 0);
	while (str[++i])
	{
		if (i == (ft_strlen(str) - 1))
			if (((ft_isalpha(str[i]) ||  str[i] == '+')
			&& !(str[i] >= '0' && str[i] <= '9')))
				continue ;
		if (!((ft_isalpha(str[i]) || (str[i] >= '0' && str[i] <= '9'))))
			export_error(str);
	}
	return (1);
}

void	init_status(t_env **env, int status)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "?", 1))
		{
			free(tmp->value);
			if (status == 0)
				tmp->value = ft_itoa(0);
			else if (status == 1)
				tmp->value = ft_itoa(1);
		}
	}
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