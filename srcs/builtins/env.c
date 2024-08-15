/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:55:12 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:30:33 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return (EXIT_FAILURE);
	temp = find_envp("_", env);
	if (!temp)
	{
		if (!env_add_var("_=/usr/bin/env", env))
			return (EXIT_FAILURE);
	}
	else
	{
		ft_free(temp->name_value);
		temp->name_value = ft_strdup("_=/usr/bin/env");
		if (!temp->name_value)
			return (EXIT_FAILURE);
	}
	while (env)
	{
		if (env->hide == false)
			ft_putendl_fd(env->name_value, STDOUT_FILENO);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
