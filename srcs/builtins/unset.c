/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:02:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:29:34 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_unset(char *command)
{
	while (*command)
	{
		if (*command == '=')
			return (0);
		command++;
	}
	return (1);
}

static int	find_variable(char *variable, t_env **env)
{
	t_env	*cur;
	t_env	*prev;

	if (*env == NULL)
		return (0);
	cur = *env;
	prev = NULL;
	if (!cur->hide && !ft_strncmp(variable, cur->name_value,
			ft_strlen(variable)) && cur->name_value[ft_strlen(variable)] == '=')
	{
		*env = cur->next;
		return (ft_free(cur->name_value), ft_free(cur), 1);
	}
	while (cur)
	{
		if (!cur->hide && !ft_strncmp(variable, cur->name_value, ft_strlen(
					variable)) && cur->name_value[ft_strlen(variable)] == '=')
		{
			prev->next = cur->next;
			return (ft_free(cur->name_value), ft_free(cur), 1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int	run_unset(char **command, t_env **env)
{
	if (!command[1])
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!verify_unset(command[1]))
		return (EXIT_FAILURE);
	if (find_variable(command[1], env) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
