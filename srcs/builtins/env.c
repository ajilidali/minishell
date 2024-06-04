/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:55:12 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/04 08:57:15 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_env(t_env *env)
{
	while (env)
	{
		ft_putendl_fd(env->name_value, STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}
