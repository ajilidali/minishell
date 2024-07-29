/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:39:18 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/29 18:09:17 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*new_node(char *name_value, bool hide)
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
	node->hide = hide;
	node->next = NULL;
	return (node);
}

t_env	*create_empty_env(void)
{
	t_env	*head;
	char	*path;
	char	*pwd;
	t_env	*node;

	head = new_node("_=/usr/bin/env", false);
	if (!head)
		return (NULL);
	if (!change_shlvl(head))
		return (free_env(head), NULL);
	node = head->next;
	path = getcwd(NULL, 0);
	if (!path)
		return (free_env(head), NULL);
	pwd = ft_strjoin("PWD=", path);
	if (!pwd)
		return (free_env(head), free(path), NULL);
	node->next = new_node(pwd, false);
	if (!node->next)
		return (free_env(head), free(path), free(pwd), NULL);
	return (free(path), free(pwd), head);
}

t_env	*copy_env(char **envp)
{
	t_env	*env;
	t_env	*head;
	int		i;

	i = 0;
	if (!envp[i])
		return (create_empty_env());
	head = new_node(envp[i++], false);
	if (!head)
		return (NULL);
	env = head;
	while (envp[i])
	{
		env->next = new_node(envp[i++], false);
		if (!env->next)
			return (free_env(head), NULL);
		env = env->next;
	}
	if (!change_shlvl(head))
		return (free_env(head), NULL);
	return (head);
}
