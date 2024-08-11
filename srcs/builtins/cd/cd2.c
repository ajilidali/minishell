/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:08:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:29:53 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		env->next = new_node("PWD=", false);
		env = env->next;
	}
	if (!is_oldpwd(new))
		env->next = new_node("OLDPWD=", false);
}

void	update_pwd(char *old_pwd, char *path, t_env *env)
{
	char	*new_path;
	t_env	*tmp_env;

	if (!old_pwd)
		old_pwd = "";
	add_pwd(env);
	new_path = get_pwd(path, old_pwd);
	if (!new_path)
		new_path = getcwd(NULL, 0);
	if (!new_path)
		exit(EXIT_FAILURE);
	tmp_env = find_envp("PWD", env);
	if (tmp_env)
	{
		ft_free(tmp_env->name_value);
		tmp_env->name_value = ft_strjoin("PWD=", new_path);
		if (!tmp_env->name_value)
			exit(EXIT_FAILURE);
	}
	tmp_env = find_envp("OLDPWD", env);
	if (tmp_env)
	{
		ft_free(tmp_env->name_value);
		tmp_env->name_value = ft_strjoin("OLDPWD=", old_pwd);
		if (!tmp_env->name_value)
			exit(EXIT_FAILURE);
	}
	ft_free(new_path);
}
