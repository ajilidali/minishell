/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:41:54 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/29 13:45:35 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT) // ctrl c
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT) // ctrl "\"
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handler(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = handler;
	act.sa_flags = 0;
	
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
