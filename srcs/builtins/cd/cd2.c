/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:08:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/16 19:14:26 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd(t_env *env)
{
	while (env)
	{
		if (ft_strncmp("PWD=", env->name_value, 4) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_oldpwd(t_env *env)
{
	while (env)
	{
		if (ft_strncmp("OLDPWD=", env->name_value, 7) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	add_pwd(t_env *env)
{
	t_env	*new;

	new = env;
	while (env->next)
		env = env->next;
	if (!is_pwd(new))
	{
		env->next = new_node("PWD=");
		env = env->next;
	}
	if (!is_oldpwd(new))
		env->next = new_node("OLDPWD=");
}

void	update_pwd(char *old_pwd, char *path, t_env *env)
{
	char	*new_path;

	old_pwd = ft_strdup(old_pwd);
	add_pwd(env);
	new_path = get_pwd(path, old_pwd);
	if (!new_path)
		new_path = getcwd(NULL, 0);
	if (!new_path)
		return (free(old_pwd));
	while (env)
	{
		if (ft_strncmp("PWD=", env->name_value, 4) == 0)
		{
			free(env->name_value);
			env->name_value = ft_strjoin("PWD=", new_path);
		}
		if (ft_strncmp("OLDPWD=", env->name_value, 7) == 0)
		{
			free(env->name_value);
			env->name_value = ft_strjoin("OLDPWD=", old_pwd);
		}
		env = env->next;
	}
	free(old_pwd);
	free(new_path);
}
