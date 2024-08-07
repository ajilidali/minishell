/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:41:54 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/07 22:03:15 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void handler_reset(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("YO\n", 1);
	return ;
}

void reset_signal_handlers(void)
{
    struct sigaction act;

    sigemptyset(&act.sa_mask);
	ft_putendl_fd("RESET", STDERR_FILENO);
    act.sa_handler = handler_reset; // Reset to default handler
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
}

void	setup_signal_handler(void)
{
	struct sigaction	act;

	ft_putendl_fd("CREATE", STDERR_FILENO);
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_DFL;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
