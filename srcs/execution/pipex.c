/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/06/06 21:01:53 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i++], "/");
		path = ft_strjoin(part_path, cmd);
		if (!part_path || !path)
			return (freetab(paths), free(part_path), NULL);
		if (access(path, F_OK) == 0)
			return (freetab(paths), free(part_path), path);
		free(part_path);
		free(path);
	}
	return (freetab(paths), NULL);
}

char	*check_local_cmd(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

int	check_path(const char *path)
{
	if (access(path, F_OK) != 0)
	{
		printf("Path %s does not exist.\n", path);
		return (0);
	}
	if (chdir(path) == 0)
	{
		printf("DEDSEC: %s: is a directory.\n", path);
		chdir("..");
		return (1);
	}
	else
		return (0);
}

int execute(ASTNode *node, char **envp)
{
    char *path;

	path = NULL;
    if (!path)
        path = check_local_cmd(node->args[0]);
    if (!path)
        path = find_path(node->args[0], envp);
    if (!path) 
        return (freetab(envp), EXIT_FAILURE);	
    if (check_path(path) == 1)
        return (exit(1),0);
    if (execve(path, node->args, envp) == -1) 
        return (freetab(envp),EXIT_FAILURE);
    free(path);
    freetab(envp);
    return EXIT_FAILURE;
}
