/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:32:58 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/21 17:45:12 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void	export_error(char *str)
{
		write(2, "export: `", 9);
		ft_putstr_fd(str, 2);
		write(2, "': not a valide identifier\n", 27);
}
int	export_valid_check(char *str, t_env ***env)
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


void	unset_error(char *str)
{
		write(2, "unset: `", 9);
		ft_putstr_fd(str, 2);
		write(2, "': not a valide identifier\n", 27);
}
int		unset_valid_check(char *str, t_env ***env)
{
	int i;

	i = 0;
	if (!(ft_isalpha(str[0])))
		return (unset_error(str), 0);
	while (str[++i])
	{
		if (!((ft_isalpha(str[i]) || (str[i] >= '0' && str[i] <= '9'))))
			unset_error(str);
	}
	return (1);
}
