/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/05/22 16:52:16 by moajili          ###   ########.fr       */
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

//Alias Structs

typedef struct {
    char *cmd;
    char *value;
} Alias;


//Lexer Structs

typedef enum {
    TOKEN_WORD,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    //TOKEN_ARGS,
    //TOKEN_${},
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct {
    const char *input;
    size_t pos;
    size_t length;
} Lexer;


//Is functions
int is_quote(char c);
int is_whitespace(char c);
int is_operator(char c);

//Token assigning functions
Token lexer_operator(Lexer *lexer);
Token lexer_word(Lexer *lexer);
Token lexer_string(Lexer *lexer);
//Token lexer_args(Lexer *lexer);
//Token lexer_${} (Lexer *lexer);

//Lexer functions
Token lexer_next_token(Lexer *lexer);
Lexer lexer_init(const char *input);
void lexer_skip_whitespace(Lexer *lexer);
void lexer_advance(Lexer *lexer);
char lexer_peek(Lexer *lexer);

//Main functions
int executor(char *line, char **envp);
char *rl_shell(char *line_read);

//other functions
void print_envp(char **envp);

#endif 