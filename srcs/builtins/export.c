/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:20 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 19:09:41 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_export(char *command)
{
	int	i;

	i = 0;
	if (command[0] == '=')
		return (2);
	while (command[i])
		if (command[i++] == '=')
			return (0);
	return (1);
}

t_env	*find_envp(char *variable, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!variable || !env)
		return (NULL);
	while (variable[i] && variable[i] != '=')
		i++;
	while (env)
	{
		while (env->name_value[j] && env->name_value[j] != '=')
			j++;
		if (ft_strncmp(variable, env->name_value, i) == 0 && j == i
			&& !env->hide)
			return (env);
		env = env->next;
		j = 0;
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

int	add_node_env(char *command, t_env *env)
{
	t_env	*node;
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	node = find_envp(command, env);
	if (!node)
	{
		tmp->next = new_node(command, false);
		if (!tmp->next)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_free(node->name_value);
		node->name_value = ft_strdup(command);
		if (!node->name_value)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	run_export(char **command, t_env **env)
{
	int		i;

	i = 1;
	if (!command[1])
		return (print_env(*env));
	while (command[i])
	{
		if (verify_export(command[i]))
		{
			if (verify_export(command[i]) == 1)
				return (EXIT_SUCCESS);
			else
			{
				ft_putendl_fd("dedsec: export: `=': not a valid identifier", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
		}
		if (add_node_env(command[i], *env))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
