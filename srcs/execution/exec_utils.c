/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:20:40 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/05 17:35:08 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(t_pipex *data, int status)
{
	close(data->fd1);
	close(data->fd2);
	free(data);
	exit(status);
}

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

void	open_files(t_pipex *data, char **argv, int argc)
{
	data->fd1 = open(argv[1], O_RDONLY);
	data->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd1 == -1 || data->fd2 == -1)
		exit_process(data, EXIT_SUCCESS);
	data->nbr_cmd = argc - 1;
}

void check_path(char *path)
{
	struct stat	path_info;

	if (stat(path, &path_info) == -1)
	{
		perror(path);
		//print_errors(path, ER_NO_FILE_DIR);
		exit(127);
	}
	if (S_ISDIR(path_info.st_mode))
	{
		print_errors(path, ER_IS_DIR);
		exit(126);
	}
	else if (!S_ISREG(path_info.st_mode))
	{
		print_errors(path, ER_NO_FILE_DIR);
		exit(127);
	}
	else if (S_ISREG(path_info.st_mode) && !(path_info.st_mode & S_IXUSR))
	{
		print_errors(path, ER_PERM_DENIED);
		exit(126);
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
			return (free(paths), free(path), freetab(split_path), NULL);
		free(paths);
		if (!access(path, X_OK))
			return (freetab(split_path), path);
		free(path);
		i++;
	}
	return (freetab(split_path), NULL);
}
