/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/08/09 22:22:46 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	setup_redirect_in(ASTNode *node, size_t i)
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
			return (1);
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
			return (1);
		}
	}
	return (0);
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
		while (1)
		{
			str = get_next_line(STDIN_FILENO);
			if ((ft_strlen(str)) > 1 && !ft_strncmp(str,
					node->redirections[i].file,
					ft_strlen(node->redirections[i].file)))
				return (free(str), close(0), get_next_line(0), exit(0));
			ft_putstr_fd(str, pipefd[1]);
			free(str);
		}
		close(pipefd[1]);
		close(pipefd[0]);
		return (free(str), close(0), get_next_line(0), exit(0));
	}
	wait(NULL);
}

static int	setup_redirect_out(ASTNode *node, size_t i)
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
			return (1);
		}
	}
	return (0);
}

int	setup_redirections(ASTNode *node)
{
	size_t	i;

	i = 0;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	while (i < node->redirections_count)
	{
		if (setup_redirect_in(node, i))
			return (1);
		if (setup_redirect_out(node, i))
			return (1);
		i++;
	}
	return (0);
}
