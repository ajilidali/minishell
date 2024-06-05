/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:55:12 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/05 08:31:19 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_env(t_env *env)
{
	if (!env)
		return (EXIT_FAILURE);
	while (env)
	{
		ft_putendl_fd(env->name_value, STDOUT_FILENO);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
