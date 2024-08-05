/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/08/04 15:21:57 by hclaude          ###   ########.fr       */
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
# include <fcntl.h>
# include "../libft/libft.h"
# include <signal.h>
# include <sys/stat.h>
# include <stdbool.h>

# define FREE_GB 1
# define COPY 10 // Flag for copying envp to global

# define FD_IN 0
# define FD_HD 1
# define FD_OUT 2
# define FD_ADDOUT 3

# define ER_SYNTAX_ERROR 1
# define ER_QUOTE_ERROR 2
# define ER_REDIRECT_ERROR 3
# define ER_CMD_NOT_FOUND 4
# define ER_PERM_DENIED 5
# define ER_NO_FILE_DIR 6
# define ER_NO_FILE 7
# define ER_IS_DIR 8

# define MAX_ARGS 1024
# define MAX_REDIRS 5

//Garbage collector struct
typedef struct s_gc
{
	void		*str;
	struct s_gc	*next;
}	t_gc;

//Redirection struct
typedef struct s_redirection
{
	int		flag;  // ">" or ">>" or "<" or "<<"
	char	*file; // the file name for redirection
}	t_redirection;

//Env struct
typedef struct s_env
{
	char			*name_value;
	bool			hide;
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
	TOKEN_EMPTY,
	TOKEN_STRING,
	TOKEN_VARIABLE,
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
	char			**args; // For command nodes
	int				fd_in;
	int				fd_out;
	int				save_in;
	int				save_out;
	struct ASTNode	*left; // For pipe nodes
	struct ASTNode	*right; // For pipe nodes
	t_redirection	*redirections; // Array containing redirections
	size_t			redirections_count; // Number of redirections
	size_t			args_capacity;
	size_t			redirections_capacity;
	size_t			args_count;
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
	t_env	*env;
	char	*line;
	int		exit_code;
} MS;

// Extern global variable
//extern MS g_ms;

// Built-in functions
int			is_local_fct(MS *mini, ASTNode *node);
int			run_echo(char **command);
int			run_cd(char **command, t_env *env);
int			run_export(char **command, t_env **env);
int			run_unset(char **command, t_env **env);
int			run_pwd(void);
int			run_env(t_env *env);
int			run_alias(MS *mini, ASTNode *node);
int			run_exit(char **command, MS *mini);

// Env functions
void		free_env(t_env *env);
char		**get_tabenv(t_env *env);
t_env		*copy_env(char **envp);
t_env		*new_node(char *name_value, bool hide);
t_list		*copy_pwd(char *pwd, char *env_pwd);
t_env		*create_empty_env(void);

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

char		*replace_variables(char *input);
Token		create_token(TokenType type, char *value);

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
void		execute_ast(ASTNode *node, MS *mini);
int			ft_fork_right(ASTNode *node, MS *mini,int pipefd[2]);
int			ft_fork_left(ASTNode *node, MS *mini,int pipefd[2]);

// Main functions
int			executor(char *line, char **envp);
char		*rl_shell(char *line_read);
MS			*ft_init_ms(MS *mini, char **envp);

// Other functions
char		*parse_variable(char *value);
void		print_envp(char **envp);
//void		process_arguments(int argc, char *argv[]);
void		trim_whitespace(char *str);

// Pipex functions
void		exec_commands(ASTNode *node, MS *ms);
int			execute(ASTNode *node, char **envp);
char		*find_path(char *cmd, char **envp);
int			init_pipex(int nargument, char **command, char **envp);
char		*quote_master(char quote);
int			char_counter(const char *str, char c);
void		exec_pipe(ASTNode *node, MS *mini);

// Args Mgmt
char		**filter_argv(char **argv, const char *target);
int			get_argc(char *argv[]);

//beta
int			setup_redirections(ASTNode *node);

//utils
t_env		*give_envp(char **envp, int flag);
void		test_envp(t_env *env, char *str);
void		update_envp(MS *mini);
t_env		*find_envp(char *variable, t_env *env);
char		*copy_except_first_n_chars(const char *input, size_t n);
void	setup_signal_handler(void);
//void		sigint_handler(void);
char		*env_get_var(char *variable, t_env *env);
void		update_pwd(char *old_pwd, char *path, t_env *env);
char		*get_pwd(char *path, char *old_pwd);
void		check_path(char *path);
void		print_errors(char *str, int flag);
int			change_shlvl(t_env *env);
int			make_redirection(ASTNode *node);
int			env_add_var(char *var, t_env *env);
void		close_node_fd(ASTNode *node, int *pipefd);

//list for pwd
t_list		*lnew_node(char *name_value);
int			add_node(char *content, t_list *list);
void		delete_last_node(t_list *list);
void		free_list(t_list *env);

#endif // MINISHELL_H
