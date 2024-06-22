/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
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
    int fd;
    for (size_t i = 0; i < node->redirection_count; i++)
    {
        if (strcmp(node->redirections[i].type, ">") == 0)
        {
            fd = open(node->redirections[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
        }
        else if (strcmp(node->redirections[i].type, ">>") == 0)
        {
            fd = open(node->redirections[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
        }
        else if (strcmp(node->redirections[i].type, "<") == 0)
        {
            fd = open(node->redirections[i].file, O_RDONLY);
            dup2(fd, STDIN_FILENO);
        }
        else if (strcmp(node->redirections[i].type, "<<") == 0)
        {
            // Handle here-doc redirection
        }
        if (fd < 0)
        {
            perror("open");
            exit(1);
        }
        close(fd);
    }
}
