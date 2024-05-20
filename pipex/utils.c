/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by moajili           #+#    #+#             */
/*   Updated: 2024/05/20 17:32:23 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	fprintf(stderr, "\033[33;1m  envp : %s\033[m\n", envp[i]);
	if (!envp[i])
		return (fprintf(stderr, "\033[33;1m ENV is NULL, quitting...\033[m\n"),
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
		fprintf(stderr, "\033[33;1m  path : %s\033[m\n", path);
		if (access(path, F_OK) == 0)
			return (ft_freef("%s %p", paths, part_path), path);
		ft_freef("%p %p", part_path, path);
	}
    fprintf(stderr, "\033[33;1m  cmd : %s\033[m\n", cmd);
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
		return (fprintf(stderr, "\033[33;1m  All good. %s \033[m\n", cmd),
			path);
	free(path);
	return (NULL);
}

int	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = NULL;
	path = NULL;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (EXIT_FAILURE);
	path = find_path(cmd[0], envp);
	if (!path)
		path = check_local_cmd(cmd[0]);
	if (!path)
	{
		ft_freef("%s,%p", cmd, path);
		return (EXIT_FAILURE);
	}
	fprintf(stderr, "\033[33;1m%s\033[m\n", path);
	fprintf(stderr, "\033[33;1m%s\033[m\n", cmd[0]);
	if (execve(path, cmd, envp) == -1)
	{
		ft_freef("%s,%p", cmd, path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
