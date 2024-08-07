/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:01:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/07 23:45:35 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_left_node(int pipefd[2], MS *mini, ASTNode *node)
{
	mini->exit_code = setup_redirections(node);
	if (mini->exit_code)
		return (close_node_fd(node, pipefd), exit(mini->exit_code));
	if (node->fd_in != STDIN_FILENO)
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (close_node_fd(node, pipefd), exit(mini->exit_code));
	if (node->fd_out != STDOUT_FILENO)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (close_node_fd(node, pipefd), exit(mini->exit_code));
	}
	else
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (close_node_fd(node, pipefd), exit(mini->exit_code));
}

// Pipe --> Left
int	ft_fork_left(ASTNode *node, MS *mini, int pipefd[2])
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		reset_signal_handlers();
		redir_left_node(pipefd, mini, node);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_pipe(node, mini);
		exit(1);
	}
	// if le stdin est un here_doc faire un waitpid
	// sinon ne pas attendre
	waitpid(pid, &status, WNOHANG);
	return (WEXITSTATUS(status));
}
