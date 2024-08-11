/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:21:37 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:32:06 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	setup_redirect_out_pipe(list_commands *list, size_t i)
{
	if (list->redirections[i].flag == FD_OUT)
	{
		if (list->fd_out != STDOUT_FILENO)
			close(list->fd_out);
		list->fd_out = open(list->redirections[i].file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (list->fd_out == -1)
		{
			perror("DEDSEC");
			return (1);
		}
	}
	else if (list->redirections[i].flag == FD_ADDOUT)
	{
		if (list->fd_out != STDOUT_FILENO)
			close(list->fd_out);
		list->fd_out = open(list->redirections[i].file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (list->fd_out == -1)
		{
			perror("DEDSEC");
			return (1);
		}
	}
	return (0);
}

void	make_here_doc_pipe(int *pipefd, list_commands *node, size_t i)
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
				return (ft_free(str), close(0), get_next_line(0), exit(0));
			ft_putstr_fd(str, pipefd[1]);
			ft_free(str);
		}
		close(pipefd[1]);
		close(pipefd[0]);
		return (ft_free(str), close(0), get_next_line(0), exit(0));
	}
	wait(NULL);
}

static int	setup_redirect_in_pipe(list_commands *node, size_t i)
{
	int	pipefd[2];

	if (node->redirections[i].flag == FD_HD)
	{
		if (pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		make_here_doc_pipe(pipefd, node, i);
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

int	setup_redirections_pipe(list_commands *list)
{
	size_t	i;

	i = 0;
	while (i < list->redirections_count)
	{
		if (setup_redirect_in_pipe(list, i))
			return (1);
		if (setup_redirect_out_pipe(list, i))
			return (1);
		i++;
	}
	return (0);
}

int	make_redirection_pipe(list_commands *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		node->save_in = dup(STDIN_FILENO);
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			close(node->fd_in);
			close(node->fd_out);
			return (0);
		}
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		node->save_out = dup(STDOUT_FILENO);
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			close(node->fd_in);
			close(node->fd_out);
			return (0);
		}
		close(node->fd_out);
	}
	return (1);
}
