/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:20:40 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 22:05:01 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_valid_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}

void	check_path(char *path)
{
	struct stat	path_info;

	if (access(path, X_OK) == -1)
	{
		print_errors(path, ER_CMD_NOT_FOUND);
		ft_exit(127);
	}
	if (stat(path, &path_info) == -1)
	{
		perror("DEDSEC ");
		ft_exit(127);
	}
	if (S_ISDIR(path_info.st_mode))
	{
		print_errors(path, ER_IS_DIR);
		ft_exit(126);
	}
	else if (S_ISREG(path_info.st_mode) && !(path_info.st_mode & S_IXUSR))
	{
		print_errors(path, ER_PERM_DENIED);
		ft_exit(127);
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	**split_path;
	char	*path;
	char	*paths;
	int		i;

	i = get_valid_line(envp);
	if (i == -1)
		return (NULL);
	split_path = ft_split(envp[i] + 5, ':');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		paths = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(paths, cmd);
		if (!path)
			return (ft_free(paths), ft_free(path), freetab(split_path), NULL);
		ft_free(paths);
		if (!access(path, X_OK | F_OK))
			return (freetab(split_path), path);
		ft_free(path);
		i++;
	}
	return (freetab(split_path), NULL);
}
