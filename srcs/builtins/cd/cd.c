/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:16:51 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_back(t_env *env, char *old_pwd)
{
	char	*back_path;

	back_path = env_get_var("OLDPWD", env, false);
	if (!back_path)
	{
		ft_putendl_fd("DEDSEC: cd: OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	if (access(back_path, F_OK) == -1)
	{
		ft_putstr_fd("DEDSEC: cd: ", STDERR_FILENO);
		ft_putstr_fd(back_path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}
	if (chdir(back_path) == -1)
		return (1);
	ft_putendl_fd(back_path, STDOUT_FILENO);
	update_pwd(ft_strdup(old_pwd), env);
	return (0);
}

int	run_cd(char **command, t_env *env)
{
	char	*home;
	char	*old_pwd;

	if (command[1] && command[2])
		return (ft_putendl_fd("dedsec: cd: too many arguments",
				STDERR_FILENO), 1);
	old_pwd = env_get_var("PWD=", env, false);
	if (!command[1])
	{
		home = env_get_var("HOME", env, false);
		if (!home)
			return (ft_putendl_fd("DEDSEC: cd: HOME not set", 2), 1);
		if (chdir(home) == -1)
			return (perror("DEDSEC: cd:"), 1);
		return (update_pwd(ft_strdup(old_pwd), env), 0);
	}
	if (!ft_strncmp(command[1], "-", 1))
		return (get_back(env, old_pwd));
	if (chdir(command[1]) == -1)
		return (perror("DEDSEC: cd:"), 1);
	return (update_pwd(ft_strdup(old_pwd), env), 0);
}
