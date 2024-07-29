/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:02:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/29 17:01:19 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	i;
	t_env	*current;
	t_env	*previous;

	if (*env == NULL)
		return (0);
	i = ft_strlen(variable);
	current = *env;
	previous = NULL;
	if (!ft_strncmp(variable, current->name_value, i) && current->name_value[i] == '=')
	{
		*env = current->next;
		return (free(current->name_value), free(current), 1);
	}
	while (current)
	{
		if (!ft_strncmp(variable, current->name_value, i) && current->name_value[i] == '=')
		{
			previous->next = current->next;
			return (free(current->name_value), free(current), 1);
		}
		previous = current;
		current = current->next;
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
