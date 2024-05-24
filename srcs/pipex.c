/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/05/24 14:51:12 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			return (ft_freef("%s %p", paths, part_path), NULL);
		//fprintf(stderr, "\033[33;1m  path : %s\033[m\n", path);
		if (access(path, F_OK) == 0)
			return (ft_freef("%s %p", paths, part_path), path);
		//ft_freef("%p %p", part_path, path);
	}
   // fprintf(stderr, "\033[33;1m  cmd : %s\033[m\n", cmd);
	return (ft_freef("%s", paths), NULL);
}

void	error(int err)
{
	perror("c");
	exit(err);
}

char	*check_local_cmd(char *cmd)
{
	int		i;
	int		sub;
	char	*path;

	if (cmd[0] == '.' && cmd[1] == '/')
	{
		i = 2;
		sub = 2;
	}
	i = 0;
	sub = 0;
	path = malloc(sizeof(char) * ft_strlen(cmd - sub));
	if (!path)
		return (NULL);
	while (cmd[i])
	{
		path[i - sub] = cmd[i];
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (/*fprintf(stderr, "\033[33;1m  All good. %s \033[m\n", cmd),*/
			path);
	free(path);
	return (NULL);
}

int	execute(ASTNode *node, char **envp)
{
	char	*path;

	path = NULL;
	if (is_local_fct() == 0)
		return (EXIT_SUCCESS);
	if (!path)
		path = find_path(node->args[0], envp);
   // printf("path : %s\n", path);
	if (!path)
		path = check_local_cmd(node->args[0]);
	if (!path)
	{
		ft_freef("%s,%p", node->args[0], path);
		return (EXIT_FAILURE);
	}
	//fprintf(stderr, "\033[33;1m%s\033[m\n", path);
	//fprintf(stderr, "\033[33;1m%s\033[m\n", cmd[0]);
	if (execve(path, node->args, envp) == -1)
	{
		ft_freef("%s,%p", node->args[0], path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}