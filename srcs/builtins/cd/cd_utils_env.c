/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:08:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 13:20:27 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_pwd(t_env *env)
{
	t_env	*new;

	new = env;
	while (env->next)
		env = env->next;
	if (!is_pwd(new))
	{
		env->next = new_node("PWD=", false);
		env = env->next;
	}
	if (!is_oldpwd(new))
		env->next = new_node("OLDPWD=", false);
}

void	update_hide_pwd(char *new_path)
{
	t_env	*tmp_env;
	char	*value;

	tmp_env = find_envp("PWD_HIDE", give_envp(NULL, 0), true);
	value = ft_strjoin("PWD_HIDE=", new_path);
	if (!value)
		return (ft_putendl_fd("DEDSEC : Faill alloc",
				STDERR_FILENO), ft_exit(1));
	if (!tmp_env)
	{
		if (!env_add_var(value, give_envp(NULL, 0), true))
			return (ft_putendl_fd("DEDSEC : Faill alloc",
					STDERR_FILENO), ft_exit(1));
	}
	else
	{
		ft_free(tmp_env->name_value);
		tmp_env->name_value = value;
	}
}

void	change_pwd(t_env *env, char *new_path, char *old_pwd)
{
	t_env	*tmp_env;

	tmp_env = find_envp("PWD", env, false);
	if (tmp_env)
	{
		ft_free(tmp_env->name_value);
		tmp_env->name_value = ft_strjoin("PWD=", new_path);
		if (!tmp_env->name_value)
			ft_exit(EXIT_FAILURE);
	}
	tmp_env = find_envp("OLDPWD", env, false);
	if (tmp_env)
	{
		ft_free(tmp_env->name_value);
		tmp_env->name_value = ft_strjoin("OLDPWD=", old_pwd);
		if (!tmp_env->name_value)
			ft_exit(EXIT_FAILURE);
	}
	update_hide_pwd(new_path);
	ft_free(new_path);
}

void	update_pwd(char *old_pwd, t_env *env)
{
	char	*new_path;

	if (!old_pwd)
		old_pwd = "";
	add_pwd(env);
	new_path = getcwd(NULL, 0);
	if (!new_path)
		new_path = env_get_var("PWD_HIDE=", env, false);
	if (!new_path)
		new_path = "";
	change_pwd(env, new_path, old_pwd);
}
