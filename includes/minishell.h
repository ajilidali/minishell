/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/06/05 10:16:14 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

# define FREE_GB 1

//Garbage collector struct
typedef struct s_gc
{
	void		*str;
	struct s_gc	*next;
}	t_gc;

//Env struct
typedef struct s_env
{
	char			*name_value;
	struct s_env	*next;
}	t_env;

//Alias Structs
typedef struct {
	char	*cmd;
	char	*value;
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
	TokenType	type;
	char		*value;
} Token;

typedef struct {
	const char	*input;
	size_t		pos;
	size_t		length;
} Lexer;

//Abstract Syntax Tree Structs
typedef enum {
	AST_COMMAND,
	AST_PIPELINE
} ASTNodeType;

typedef struct ASTNode {
	ASTNodeType		type;
	char			**args;           // For command nodes
	struct ASTNode	*left;  // For pipe nodes
	struct ASTNode	*right; // For pipe nodes
} ASTNode;

// Parser Structs
typedef struct {
	Lexer	lexer;
	Token	current_token;
} Parser;

// Minishell Structs
typedef struct {
    Alias	*aliases;
    Lexer	lexer;
    Token	token;
    Parser	parser;
    ASTNode	*ast;
    size_t	alias_count;
    t_env	*envp;
    char	*line;
} MS;

// Extern global variable
//extern MS g_ms;

// Built-in functions
int			is_local_fct(MS *mini);
int			run_echo(char **command);
int			run_cd(char **command, t_env *env);
int			run_export(char **command, t_env **env);
int			run_unset(char **command, t_env **env);
int			run_pwd(void);
int			run_env(t_env *env);
int			run_alias(MS *mini);
void		run_exit(char **command);

// Env functions
void		free_env(t_env *env);
char		**get_tabenv(t_env *env);
t_env		*copy_env(char **envp);
t_env		*new_node(char *name_value);

// Idea : make a structure for builtins and then strcmp in vars:44 in a while,
// have to make sure can run fcts from structs

// Is functions
int			is_quote(char c);
int			is_whitespace(char c);
int			is_operator(char c);

// Token assigning functions
Token		lexer_operator(Lexer *lexer);
Token		lexer_word(Lexer *lexer);
Token		lexer_string(Lexer *lexer);

// Lexer functions
Token		lexer_next_token(Lexer *lexer);
Lexer		lexer_init(const char *input);
void		lexer_skip_whitespace(Lexer *lexer);
void		lexer_advance(Lexer *lexer);
char		lexer_peek(Lexer *lexer);

// AST & Parser functions
Parser		parser_init(const char *input);
void		parser_advance(Parser *parser);
ASTNode		*parse_command(Parser *parser);
ASTNode		*parse_pipeline(Parser *parser);
void		free_ast(ASTNode *node);
void		execute_ast(MS *mini);
void		ft_fork_right(MS *mini, int pipefd[2]);
void		ft_fork_left(MS *mini, int pipefd[2]);

// Main functions
int			executor(char *line, char **envp);
char		*rl_shell(char *line_read);
MS			*ft_init_ms(MS *mini, char **envp);

// Other functions
void		print_envp(char **envp);
//void		process_arguments(int argc, char *argv[]);
void		trim_whitespace(char *str);
void		freetab(char **str);

// Pipex functions
int			execute(ASTNode *node, char **envp);
char		*find_path(char *cmd, char **envp);

char		*quote_master(char quote);
int			quote_counter(const char *str, char quote);

#endif // MINISHELL_H
