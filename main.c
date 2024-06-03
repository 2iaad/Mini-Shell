/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:07:28 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/03 04:30:43 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac, char **av, char **envp)
{
	t_final final_cmd;
	// atexit(f);
	// rl_catch_signals = 0;
	(void)av;
	if (ac > 1)
	{
		write(2, "Error: too many arguments\n", 26);
		return (1);
	}
	init_env(&final_cmd, envp);
	read_from_input(&final_cmd);
}