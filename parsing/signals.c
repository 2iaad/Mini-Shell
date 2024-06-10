/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:51:33 by ibouram           #+#    #+#             */
/*   Updated: 2024/06/10 03:42:38 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	sig_ctrl_d(int sig)
// {
// 	(void)sig;
// 	// rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	sig_ctrl_c(int sig)
// {
	
// }
void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			ft_putstr_fd("\n", 2);
			return ;
		}
		//exit_status(0, 1);
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, signal_handle);
}
