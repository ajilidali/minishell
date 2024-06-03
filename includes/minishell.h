/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/06/03 14:06:50 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <errno.h>
#include "../includes/libft.h"

//Alias Structs
typedef struct {
    char *cmd;
    char *value;
} Alias;

//Lexer Structs
typedef enum {
    TOKEN_WORD,
    TOKEN_STRING,
    TOKEN_PIPE,
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

//Abstract Syntax Tree Structs
typedef enum {
    AST_COMMAND,
    AST_PIPELINE
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char **args;           // Argv
    struct ASTNode *left;  // pipe 
    struct ASTNode *right; // pipe 
} ASTNode;

// Parser Structs
typedef struct {
    Lexer lexer;
    Token current_token;
} Parser;

// Minishell Structs
typedef struct {
    Alias *aliases;
    Lexer lexer;
    Token token;
    Parser parser;
    ASTNode *ast;
    size_t alias_count;
    char **envp;
    char *line;
} MS;

// Extern global variable
extern MS g_ms;

// Built-in functions
int	is_local_fct(ASTNode *node);

/*ALIAS*/
int print_aliases(Alias *aliases);
Alias *ft_init_alias(void);
int ft_alias(char **argv);
int alias_finder(char *cmd);

// Idea : make a structure for builtins and then strcmp in vars:44 in a while, have to make sure can
// run fcts from structs

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

// AST & Parser functions
Parser parser_init(const char *input);
void parser_advance(Parser *parser);
ASTNode *parse_command(Parser *parser);
ASTNode *parse_pipeline(Parser *parser);
void free_ast(ASTNode *node);
void execute_ast(ASTNode *node);
void ft_fork_left(ASTNode *node, int pipefd[2]);
void ft_fork_right(ASTNode *node, int pipefd[2]);

// Main functions
int executor(char *line, char **envp);
char *rl_shell(char *line_read);
void ft_init_ms(char **envp);

// Other functions
void print_envp(char **envp);
void process_arguments(int argc, char *argv[]);
void trim_whitespace(char *str);


// Pipex functions
int	execute(ASTNode *node, char **envp);
char	*find_path(char *cmd, char **envp);

char *quote_master(char quote);
int quote_counter(const char *str, char quote);

#endif // MINISHELL_H
