/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:02:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 20:22:56 by sakaido          ###   ########.fr       */
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
		return (EXIT_SUCCESS);
	if (!verify_unset(command[1]))
		return (EXIT_SUCCESS);
	if (find_variable(command[1], env) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
