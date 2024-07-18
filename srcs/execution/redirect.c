/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/07/18 17:52:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_redirect_in(ASTNode *node, size_t i)
{
	if (node->redirections[i].flag == FD_OUT)
	{
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		node->fd_out = open(node->redirections[i].file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (node->fd_out == -1)
		{
			perror("DEDSEC");
			exit(1);
		}
	}
	else if (node->redirections[i].flag == FD_ADDOUT)
	{
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		node->fd_out = open(node->redirections[i].file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (node->fd_out == -1)
		{
			perror("DEDSEC");
			exit(1);
		}
	}
}

void	make_here_doc(int *pipefd, ASTNode *node, size_t i)
{
	int		pid;
	char	*str;
	
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		str = get_next_line(STDIN_FILENO);
		while (1)
		{
			if ((ft_strlen(str)) > 1 && !ft_strncmp(str, node->redirections[i].file, ft_strlen(str) - 1))
				exit(0);
			ft_putstr_fd(str, pipefd[1]);
			free(str);
			str = get_next_line(STDIN_FILENO);
		}
		close(pipefd[1]);
		close(pipefd[0]);
		exit(0);
	}
	wait(NULL);
}

static void	setup_redirect_out(ASTNode *node, size_t i)
{
	int	pipefd[2];
	
	if (node->redirections[i].flag == FD_HD)
	{
		if (pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		make_here_doc(pipefd, node, i);
		close(pipefd[1]);
		node->fd_in = pipefd[0];
	}
	else if (node->redirections[i].flag == FD_IN)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node->fd_in = open(node->redirections[i].file, O_RDONLY);
		if (node->fd_in == -1)
		{
			perror("DEDSEC");
			exit(1);
		}
	}
}

void	setup_redirections(ASTNode *node)
{
	size_t	i;

	i = 0;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	while (i < node->redirections_count)
	{
		setup_redirect_in(node, i);
		setup_redirect_out(node, i);
		i++;
	}
}
