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

//Minishell struct

typedef struct {
    Alias *aliases;
    Lexer lexer;
    Token token;
    char *line;
} MS;

// Extern global variable
extern MS g_ms;

// Built-in functions
void is_local_fct(char* str);
void print_aliases(Alias *aliases);
Alias *ft_init_vars(void);
void ft_alias(void);
void ft_init_ms(void);

// Is functions
int is_quote(char c);
int is_whitespace(char c);
int is_operator(char c);

// Token assigning functions
Token lexer_operator(Lexer *lexer);
Token lexer_word(Lexer *lexer);
Token lexer_string(Lexer *lexer);

// Lexer functions
Token lexer_next_token(Lexer *lexer);
Lexer lexer_init(const char *input);
void lexer_skip_whitespace(Lexer *lexer);
void lexer_advance(Lexer *lexer);
char lexer_peek(Lexer *lexer);

// Main functions
int executor(char *line, char **envp);
char *rl_shell(char *line_read);

// Other functions
void print_envp(char **envp);

#endif // MINISHELL_H
