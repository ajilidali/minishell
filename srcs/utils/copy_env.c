/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:39:18 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:20:39 by hclaude          ###   ########.fr       */
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
		ft_free(tmp->name_value);
		ft_free(tmp);
	}
}

t_env	*new_node(char *name_value, bool hide)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (!name_value)
		return (NULL);
	node->name_value = ft_strdup(name_value);
	if (!node->name_value)
	{
		ft_free(node);
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
		return (free_env(head), ft_free(path), NULL);
	node->next = new_node(pwd, false);
	if (!node->next)
		return (free_env(head), ft_free(path), ft_free(pwd), NULL);
	return (ft_free(path), ft_free(pwd), head);
}

int	check_pwd(t_env *head)
{
	t_env	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	tmp = find_envp("PWD", head, false);
	if (!tmp)
	{
		if (!env_add_var("PWD=", head, false))
			return (free(pwd), 0);
	}
	if (access(env_get_var("PWD", head, false), F_OK) != 0)
	{
		tmp = find_envp("PWD", head, false);
		if (!tmp)
			return (free(pwd), 0);
		tmp->name_value = ft_strjoin("PWD=", pwd);
		if (!tmp->name_value)
			return (free(pwd), 0);
	}
	return (free(pwd), 1);
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
	if (!check_pwd(head))
		return (free_env(head), NULL);
	if (!change_shlvl(head))
		return (free_env(head), NULL);
	return (head);
}
