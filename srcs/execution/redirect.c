/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/06/25 17:28:28 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

void setup_redirections(ASTNode *node)
{
	size_t i;
	int fd;

	i = 0;
	while (i < node->redirections_count)
	{
		if (strcmp(node->redirections[i].type, ">") == 0)
		{
			fd = open(node->redirections[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(node->redirections[i].type, ">>") == 0)
		{
			fd = open(node->redirections[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(node->redirections[i].type, "<<") == 0)
		{
			//heredoc
		}
		else if (strcmp(node->redirections[i].type, "<") == 0)
		{
			fd = open(node->redirections[i].file, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
}
