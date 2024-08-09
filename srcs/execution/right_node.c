/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:01:40 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/09 16:16:10 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_right_node(int pipefd[2], MS *mini, ASTNode *node)
{
	mini->exit_code = setup_redirections(node);
	if (mini->exit_code)
		return (close_node_fd(node, pipefd), exit(mini->exit_code));
	if (node->fd_in != STDIN_FILENO)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (close_node_fd(node, pipefd), exit(1));
	}
	else
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (close_node_fd(node, pipefd), exit(1));
	if (node->fd_out != STDOUT_FILENO)
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (close_node_fd(node, pipefd), exit(1));
}

// Pipe --> Right
int	ft_fork_right(ASTNode *node, MS *mini, int pipefd[2])
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		reset_signal_handlers();
		redir_right_node(pipefd, mini, node);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_pipe(node, mini);
		exit(1);
	}
	wait_pids(pid, 1);
	waitpid(pid, &status, WNOHANG);
	return (WEXITSTATUS(status));
}
