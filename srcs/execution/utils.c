/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:52:46 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/01 16:55:55 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_node_fd(ASTNode *node)
{
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
}
