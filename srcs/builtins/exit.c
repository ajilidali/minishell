/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:46:34 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:51:27 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	run_exit(char **command, MS *mini)
{
	int	exit_value;

	exit_value = mini->exit_code;
	clear_history();
	if (!command[1])
		return (free_env(give_envp(NULL, 0)), ft_exit(exit_value), exit_value);
	if (command[2])
	{
		ft_putendl_fd("DEDSEC: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	free_env(give_envp(NULL, 0));
	if (!valid_value(command[1]))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("DEDSEC: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (ft_exit(2), 2);
	}
	exit_value = ft_atoi(command[1]);
	if (exit_value > 255)
		return (ft_exit(exit_value % 256), exit_value % 256);
	return (ft_exit(exit_value), exit_value);
}
