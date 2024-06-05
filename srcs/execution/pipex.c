/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/06/05 14:17:25 by moajili          ###   ########.fr       */
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
	//fprintf(stderr, "\033[33;1m  envp : %s\033[m\n", envp[i]);
	if (!envp[i])
		return (/*fprintf(stderr, "\033[33;1m ENV is NULL, quitting...\033[m\n"),*/
			NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] && errno != ENOMEM)
	{
		part_path = ft_strjoin(paths[i++], "/");
		path = ft_strjoin(part_path, cmd);
		if (!part_path || !path)
			return (freetab(paths), free(part_path), NULL);
		//fprintf(stderr, "\033[33;1m  path : %s\033[m\n", path);
		if (access(path, F_OK) == 0)
			return (freetab(paths), free(part_path), path);
		//ft_freef("%p %p", part_path, path);
	}
    // fprintf(stderr, "\033[33;1m  cmd : %s\033[m\n", cmd);
	return (freetab(paths), NULL);
}

void	error(int err)
{
	perror("c");
	exit(err);
}

char	*check_local_cmd(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (/*fprintf(stderr,"\033[33;1m  OK \n cmd : %s \033[m\n",cmd),*/cmd);
	return (NULL);
}

int	execute(ASTNode *node, char **envp)
{
	char	*path;
	//int i;

	//i = 0;
	path = NULL;
	if (!path)
		path = check_local_cmd(node->args[0]);
	if (!path)
		path = find_path(node->args[0], envp);
	if (!path)
	{
		free(path);
		freetab(envp);
		return (EXIT_FAILURE);
	}
	if (execve(path, node->args, envp) == -1)
	{
		free(path);
		freetab(envp);
		free(node->args[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
