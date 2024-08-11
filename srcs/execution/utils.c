/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:52:46 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 20:37:45 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_is_local(char *cmd)
{
	if (!cmd)
		return (1);
	//if (ft_strcmp(cmd, "alias") == 0)
	//	return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
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
