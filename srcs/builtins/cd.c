/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/04 16:10:25 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	change_pwd(char *old_path, t_env *env)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	add_pwd(env);
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
			env->name_value = ft_strjoin("OLDPWD=", old_path);
		}
		env = env->next;
	}
	free(old_path);
	free(new_path);
}

int	run_cd(char **command, t_env *env)
{
	char	*home;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!command[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (0);
		}
		if (chdir(home) == -1)
		{
			printf("cd: %s: %s\n", command[1], strerror(errno));
			return (0);
		}
		return (change_pwd(old_pwd, env), 1);
	}
	if (chdir(command[1]) == -1)
	{
		printf("cd: %s: %s\n", command[1], strerror(errno));
		return (0);
	}
	return (change_pwd(old_pwd, env), 1);
}
