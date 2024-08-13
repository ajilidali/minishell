/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:52:46 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/13 21:23:28 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	ft_exit(1);
}

void	close_node_fd(t_astnode *node, int *pipefd)
{
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	if (pipefd)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
}
