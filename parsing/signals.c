/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:51:33 by ibouram           #+#    #+#             */
/*   Updated: 2024/08/01 01:36:13 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		exit_status(1, 1);
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handle_2(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		close(0);
		exit_status(1, 1);
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, signal_handle);
}
