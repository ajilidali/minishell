/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:20 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/05 08:37:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_export(char *command)
{
	int	i;

	i = 0;
	while (command[i] && command[i] != '=')
	{
		i++;
	}
	if (command[i++] == '=' && command[i] != '=')
		return (1);
	return (0);
}

static t_env	*find_variable(char *variable, t_env *env)
{
	int	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(variable, env->name_value, i) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	print_env(t_env *env)
{
	if (!env)
		return (EXIT_SUCCESS);
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(env->name_value, STDOUT_FILENO);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	run_export(char **command, t_env **env)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *env;
	if (!command[1])
		return (print_env(*env));
	if (!verify_export(command[1]))
		return (EXIT_SUCCESS);
	while (tmp->next)
		tmp = tmp->next;
	node = find_variable(command[1], *env);
	if (!node)
	{
		tmp->next = new_node(command[1]);
		if (!tmp->next)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	free(node->name_value);
	node->name_value = ft_strdup(command[1]);
	if (!node->name_value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
