/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:46:34 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/05 10:30:49 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_value(char *value)
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

void	run_exit(char **command) // Besoin du dernier exit_code
{
	int	exit_value;

	rl_clear_history();
	if (!command[1])
		exit(/*LAST EXIT CODE*/0);
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
