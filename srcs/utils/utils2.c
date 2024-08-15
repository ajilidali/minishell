/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:11:57 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:21:40 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_add_var(char *var, t_env *env, bool hide)
{
	t_env	*last;

	last = env;
	while (last->next)
		last = last->next;
	last->next = new_node(var, hide);
	if (!last->next)
		return (0);
	return (1);
}

char	*env_get_var(char *variable, t_env *env, bool flag)
{
	int	i;

	i = 0;
	while (env)
	{
		while (env->name_value[i] && env->name_value[i] != '=')
			i++;
		if (ft_strncmp(env->name_value, variable, i) == 0 && env->hide == flag)
			return (env->name_value + (i + 1));
		env = env->next;
		i = 0;
	}
	return (NULL);
}

int	change_shlvl(t_env *env)
{
	t_env	*node_shlvl;
	int		shlvl;
	char	*str_lvl;
	char	*new_lvl;

	str_lvl = env_get_var("SHLVL=", env, false);
	node_shlvl = find_envp("SHLVL=", env, false);
	if (!node_shlvl)
		return ((void)env_add_var("SHLVL=0", env, false), 1);
	shlvl = ft_atoi(str_lvl) + 1;
	ft_free(node_shlvl->name_value);
	new_lvl = ft_itoa(shlvl);
	if (!new_lvl)
		return (0);
	node_shlvl->name_value = ft_strjoin("SHLVL=", new_lvl);
	ft_free(new_lvl);
	if (!node_shlvl->name_value)
		return (0);
	return (1);
}

t_env	*give_envp(char **envp, int flag)
{
	static t_env	*env = NULL;

	if (flag == COPY && envp)
	{
		env = new_node("header", true);
		if (!env)
			return (NULL);
		if (!env_add_var(ft_strjoin("PWD_HIDE=", getcwd(NULL, 0)), env, true))
			return (NULL);
		env->next->next = copy_env(envp);
		if (!env->next)
			return (free_env(env), NULL);
	}
	return (env);
}
