/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:52:46 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/06 16:14:14 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_is_local(ASTNode *node)
{
	if (!node->args[0])
		return (1);
	if (ft_strcmp(node->args[0], "alias") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(node->args[0], "exit") == 0)
		return (1);
	return (0);
}

void	close_node_fd(ASTNode *node, int *pipefd)
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
