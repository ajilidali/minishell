/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/07/03 16:43:48 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

void setup_redirections(ASTNode *node)
{
	size_t i;

	i = 0;
	while (i < node->redirections_count)
	{
		if (node->redirections[i].flag == FD_OUT)
		{
			node->fd_out = open(node->redirections[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (node->fd_out == -1)
			{
				perror("DEDSEC\n");
				//ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
				//ft_putstr_fd(node->redirections[i].file, STDERR_FILENO);
				//ft_putendl_fd(strerror, STDERR_FILENO);
				exit(1);
			}
		}
		else if (node->redirections[i].flag == FD_ADDOUT)
		{
			node->fd_out = open(node->redirections[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (node->fd_out == -1)
			{
				perror("DEDSEC\n");
				//ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
				//ft_putstr_fd(node->redirections[i].file, STDERR_FILENO);
				//ft_putendl_fd(strerror, STDERR_FILENO);
				exit(1);
			}
		}
		else if (node->redirections[i].flag == FD_HD)
		{
			//heredoc
		}
		else if (node->redirections[i].flag == FD_IN)
		{
			node->fd_in = open(node->redirections[i].file, O_RDONLY);
			if (node->fd_in == -1)
			{
				perror("DEDSEC\n");
				//ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
				//ft_putstr_fd(node->redirections[i].file, STDERR_FILENO);
				//ft_putendl_fd(strerror, STDERR_FILENO);
				exit(1);
			}
		}
		i++;
	}
}
