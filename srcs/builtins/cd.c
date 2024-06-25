/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/18 18:08:26 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_back(t_env *env, char *old_pwd)
{
	char	*back_path;

	back_path = env_get_var("OLDPWD", env);
	if (!back_path)
	{
		ft_putendl_fd("DEDSEC: cd: OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	if (chdir(back_path) == -1)
		return (1);
	update_pwd(old_pwd, env);
	return (0);
}

int	run_cd(char **command, t_env *env)
{
	char	*home;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!command[1])
	{
		home = env_get_var("HOME", env);
		if (!home)
			return (ft_putendl_fd("cd: HOME not set", 2), 1);
		if (chdir(home) == -1)
		{
			printf("cd: %s: %s\n", command[1], strerror(errno));
			return (1);
		}
		return (update_pwd(old_pwd, env), 0);
	}
	if (!ft_strncmp(command[1], "-", 1))
		return (get_back(env, old_pwd));
	if (chdir(command[1]) == -1)
	{
		printf("cd: %s: %s\n", command[1], strerror(errno));
		return (1);
	}
	return (update_pwd(old_pwd, env), 0);
}
