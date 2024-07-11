/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/10 18:42:42 by hclaude          ###   ########.fr       */
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
	update_pwd(old_pwd, env);
	return (0);
}

void	get_pwd(char *pwd, t_env *env)
{
	//struct stat	path_info;
	//char		**split_pwd;
	//int			i;
	//char		*path;
	t_list		*list;
	char		*new_pwd;
	char		*temp_pwd;

	//i = 0;
	char *env_pwd = env_get_var("PWD", env);
	list = copy_pwd(pwd, env_pwd);
	if (!list)
		return ;
	env = env->next;
	temp_pwd = NULL;
	new_pwd = ft_strdup("");
	while (list)
	{
		// ou alors backslash en seconde string
		//printf("%s ", (char *)list->content);
		temp_pwd = ft_strjoin(new_pwd, (char *)list->content);
		if (new_pwd)
			free(new_pwd);
		if (!temp_pwd)
			return ;
		new_pwd = temp_pwd;
		list = list->next;
	}
	printf("pwd = %s\n", new_pwd);
	//split_pwd = ft_split(env_get_var("PWD", env), '/');
	//env = find_envp("PWD=", env);
	//while (split_pwd[i])
	//{
	//	if (access(split_pwd[i], F_OK))
	//		chdir(split_pwd[i]);
	//	else
	//		return ;
	//	path = ft_strjoin("/", split_pwd[i]);
	//	env->name_value = ft_strjoin(env->name_value, path);
	//	//stat(split_pwd[i], &path_info);

	//}
}

int	run_cd(char **command, t_env *env)
{
	char	*home;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	get_pwd(command[1], env);
	if (!command[1])
	{
		home = env_get_var("HOME", env);
		if (!home)
			return (ft_putendl_fd("DEDSEC: cd: HOME not set", 2), 1);
		if (chdir(home) == -1)
		{
			printf("DEDSEC: cd: %s: %s\n", home, strerror(errno));
			return (1);
		}
		return (update_pwd(old_pwd, env), 0);
	}
	if (!ft_strncmp(command[1], "-", 1))
		return (get_back(env, old_pwd));
	if (chdir(command[1]) == -1)
	{
		printf("DEDSEC: cd: %s: %s\n", command[1], strerror(errno));
		return (1);
	}
	return (update_pwd(old_pwd, env), 0);
}




