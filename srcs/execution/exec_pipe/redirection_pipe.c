/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:21:37 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 11:02:02 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	setup_redirect_out_pipe(t_lst_cmd *list, size_t i)
{
	if (list->redirections[i].flag == FD_OUT)
	{
		if (list->fd_out != STDOUT_FILENO)
			close(list->fd_out);
		list->fd_out = open(list->redirections[i].file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (list->fd_out == -1)
			return (perror("DEDSEC"), 1);
	}
	else if (list->redirections[i].flag == FD_ADDOUT)
	{
		if (list->fd_out != STDOUT_FILENO)
			close(list->fd_out);
		list->fd_out = open(list->redirections[i].file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (list->fd_out == -1)
			return (perror("DEDSEC"), 1);
	}
	return (0);
}

void	make_here_doc_pipe(int *pipefd, t_lst_cmd *node, size_t i)
{
	char	*str;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, handle_sigint_heredoc);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (!str || ft_strlen(str) == 0)
			return (close(pipefd[0]), close(pipefd[1]),
				write(2, "\b\b\b", 4), write(2, "\n", 1), ft_exit(0));
		if ((ft_strlen(str)) > 1 && !ft_strncmp(str,
				node->redirections[i].file,
				ft_strlen(node->redirections[i].file)))
			return (close(pipefd[0]), close(pipefd[1]), ft_exit(0));
		ft_putstr_fd(replace_variables(str), pipefd[1]);
		ft_free(str);
	}
}

static int	setup_redirect_in_pipe(t_lst_cmd *node, size_t i)
{
	int	pipefd[2];

	if (node->redirections[i].flag == FD_HD)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		if (pipe(pipefd) == -1)
			ft_exit(EXIT_FAILURE);
		if (monitoring_hd_pipe(pipefd, node, i))
			return (ft_putendl_fd("Heredoc fail",
					STDERR_FILENO), 1);
	}
	else if (node->redirections[i].flag == FD_IN)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node->fd_in = open(node->redirections[i].file, O_RDONLY);
		if (node->fd_in == -1)
			return (perror("DEDSEC"), 1);
	}
	return (0);
}

int	setup_redirections_pipe(t_lst_cmd *list)
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

int	make_redirection_pipe(t_lst_cmd *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		if (node->fd_in < 0)
			return (0);
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (0);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (node->fd_out < 0)
			return (0);
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (0);
	}
	return (1);
}
