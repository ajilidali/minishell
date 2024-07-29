/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:46:34 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/29 14:38:04 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_value(char *value)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (value[i] == '-' || value[i] == '+')
	{
		sign++;
		i++;
	}
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (0);
		i++;
	}
	if (i - sign >= 20)
		return (0);
	return (1);
}

void	run_exit(char **command, MS *mini)
{
	ft_putendl_fd("EXIT", STDERR_FILENO);
	int	exit_value;

	clear_history();
	if (!command[1])
		exit(mini->exit_code);
	if (!valid_value(command[1]))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("DEDSEC: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	exit_value = ft_atoi(command[1]);
	if (exit_value > 255)
		exit(exit_value % 256);
	exit(2);
}
