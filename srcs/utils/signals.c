/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:41:54 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 18:44:53 by hclaude          ###   ########.fr       */
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
		ft_putstr_fd("  \b\b", STDOUT_FILENO);
	}
}

void	handler_backslash(int sig)
{
	ft_putendl_fd("Quit: 3\n", STDOUT_FILENO);
	give_mini(NULL, 0)->exit_code = 131;
	(void)sig;
}

void	handler_ctrlc(int sig)
{
	write(1, "\n", 1);
	give_mini(NULL, 0)->exit_code = 130;
	(void)sig;
}

void	handler_sleep(int signal_quit)
{
	signal(SIGINT, handler_ctrlc);
	signal(SIGQUIT, handler_backslash);
	(void)signal_quit;
}

void	setup_signal_handler(int flag)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	if (flag == 1)
	{
		act.sa_handler = handler;
		act.sa_flags = 0;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
	else if (flag == 2)
	{
		handler_sleep(0);
		return ;
	}
}
