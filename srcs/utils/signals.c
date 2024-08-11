/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:41:54 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 18:31:05 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		give_mini(NULL, 0)->exit_code = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		give_mini(NULL, 0)->exit_code = 0;
	}
}

void	handler_reset(int signal)
{
	(void)signal;
	ft_exit(0);
	return ;
}

void	reset_signal_handlers(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = handler_reset;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	handler_sleep(int signal)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	(void)signal;
}

void	setup_signal_handler(int flag)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	if (flag == 1)
	{
		act.sa_handler = handler;
	}
	else if (!flag)
	{
		sigemptyset(&act.sa_mask);
		act.sa_handler = handler_reset;
	}
	else if (flag == 2)
	{
		sigemptyset(&act.sa_mask);
		act.sa_handler = handler_sleep;
	}
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
