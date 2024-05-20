/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:54:02 by moajili           #+#    #+#             */
/*   Updated: 2024/05/20 14:32:57 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error(EBADFD);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	if (close(fd[0]) == -1)
		error(EBADFD);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error(EBADFD);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

int	pipex(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error(1);
		pid1 = fork();
		if (pid1 == -1)
			error(1);
		if (pid1 == 0)
			child_process(argv, envp, fd);
		//	waitpid(pid1, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
		return (ft_putstr_fd("Error: Bad arguments\nUsage: ./pipex <file1> <cmd1> <cmd2> <file2>\n",
				1), 1);
	return (0);
}
