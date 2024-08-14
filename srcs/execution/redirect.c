/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 18:27:51 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	setup_redirect_out(t_astnode *node, size_t i)
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

static void	make_here_doc(int *pipefd, t_astnode *node, size_t i)
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

static int	monitoring_hd(int *pipefd, t_astnode *node, size_t	i)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		make_here_doc(pipefd, node, i);
	else
	{
		setup_signal_handler(2);
		waitpid(pid, &status, 0);
		close(pipefd[1]);
		give_mini(NULL, 0)->exit_code = WEXITSTATUS(status);
		if (WEXITSTATUS(status))
			return (1);
		node->fd_in = dup(pipefd[0]);
		close(pipefd[0]);
		if (node->fd_in == -1)
			return (1);
	}
	return (0);
}

static int	setup_redirect_in(t_astnode *node, size_t i)
{
	int	pipefd[2];

	if (node->redirections[i].flag == FD_HD)
	{
		if (pipe(pipefd) == -1)
			ft_exit(EXIT_FAILURE);
		if (monitoring_hd(pipefd, node, i))
			return (1);
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

int	setup_redirections(t_astnode *node)
{
	size_t	i;

	i = 0;
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->save_in = dup(STDIN_FILENO);
	node->save_out = dup(STDOUT_FILENO);
	if (node->save_in == -1 || node->save_out == -1)
		return (ft_putendl_fd("DEDSEC : STDIN and STDOUT not dup",
				STDERR_FILENO), ft_exit(1), 1);
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
