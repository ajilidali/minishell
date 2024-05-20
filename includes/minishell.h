/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/05/20 17:46:54 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/libft.h"
#include "../includes/pipex.h"

#define MAX_TOKEN_LENGTH 1024
#define MAX_TOKEN_COUNT 128

typedef enum {
    TOKEN_NBR,
    TOKEN_CMD,
    TOKEN_PIPE,
    TOKEN_TERMINATOR
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

int executor(char *line, char **envp);
char *rl_shell(char *line_read);

#endif 