/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/06/06 21:01:53 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

void setup_redirections(ASTNode *node)
{
    for (size_t i = 0; i < node->redirections_count; ++i)
    {
        int fd;
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
    }
}
