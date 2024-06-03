/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:39:18 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 16:50:34 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name_value);
		free(tmp);
	}
}

t_env	*new_node(char *name_value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name_value = ft_strdup(name_value);
	if (!node->name_value)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

t_env	*copy_env(char **envp)
{
	t_env	*env;
	t_env	*head;
	int		i;

	i = 0;
	head = new_node(envp[i++]);
	if (!head)
		return (NULL);
	env = head;
	while (envp[i])
	{
		env->next = new_node(envp[i++]);
		if (!env->next)
			return (free_env(head), NULL);
		env = env->next;
	}
	return (head);
}
