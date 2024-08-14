/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 18:21:43 by hclaude          ###   ########.fr       */
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

# define COPY 10

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

//PID struct
typedef struct s_pidl
{
	int				pid;
	struct s_pidl	*next;
}					t_pidl;

//Redirection struct
typedef struct s_redirection
{
	int		flag;
	char	*file;
}	t_redirection;

//Env struct
typedef struct s_env
{
	char			*name_value;
	bool			hide;
	struct s_env	*next;
}	t_env;

//Alias Structs
typedef struct
{
	char	*cmd;
	char	*value;
} Alias;

//Lexer Structs
typedef enum
{
	TOKEN_WORD,
	TOKEN_EMPTY,
	TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_PIPE,
	TOKEN_OPERATOR,
	TOKEN_EOF
} TokenType;

typedef struct
{
	TokenType	type;
	char		*value;
} Token;

typedef struct
{
	const char	*input;
	size_t		pos;
	size_t		length;
}	Lexer;

//Abstract Syntax Tree Structs
typedef enum
{
	AST_COMMAND,
	AST_PIPELINE,
	AST_ERR
}	ASTNodeType;

typedef struct s_astnode
{
	ASTNodeType			type;
	char				**args; // For command nodes
	int					fd_in;
	int					fd_out;
	int					save_in;
	int					save_out;
	struct s_astnode	*left; // For pipe nodes
	struct s_astnode	*right; // For pipe nodes
	t_redirection		*redirections; // Array containing redirections
	size_t				redirections_count; // Number of redirections
	size_t				args_capacity;
	size_t				redirections_capacity;
	size_t				args_count;
}	t_astnode;

typedef struct s_lst_cmd
{
	struct s_lst_cmd	*next;
	char				**args;
	int					fd_in;
	int					fd_out;
	t_redirection		*redirections;
	size_t				redirections_count; // Number of redirections
	size_t				args_capacity;
	size_t				redirections_capacity;
	size_t				args_count;
}	t_lst_cmd;

// Parser Structs
typedef struct
{
	Lexer	lexer;
	Token	current_token;
} Parser;

// Minishell Structs
typedef struct s_ms
{
	Alias		*aliases;
	Lexer		lexer;
	Token		token;
	Parser		parser;
	t_astnode	*ast;
	size_t		alias_count;
	t_env		*env;
	char		*line;
	int			exit_code;
}	t_ms;

// Built-in functions
int			is_local_fct(t_ms *mini, t_astnode *node);
int			run_echo(char **command);
int			run_cd(char **command, t_env *env);
int			run_export(char **command, t_env **env);
int			run_unset(char **command, t_env **env);
int			run_pwd(void);
int			run_env(t_env *env);
int			run_alias(t_ms *mini, t_astnode *node);
int			run_exit(char **command, t_ms *mini);

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
int			is_whitespace(char c);
int			is_operator(char c);

// Token assigning functions
Token		lexer_operator(Lexer *lexer);
Token		lexer_word(Lexer *lexer);
Token		lexer_string(Lexer *lexer);
char		*replace_variables(char *in);
Token		crt_tkn(TokenType type, char *value);

// Lexer functions
Token		lexer_next_token(Lexer *lexer);
Lexer		lexer_init(const char *input);
char		lp(Lexer *lexer);

// AST & Parser functions
Parser		parser_init(const char *input);
void		parser_advance(Parser *parser);
t_astnode	*parse_command(Parser *parser);
t_astnode	*parse_pipeline(Parser *parser);
void		free_ast(t_astnode *node);
int			check_ast_for_errors(t_astnode *node);

// Main functions
char		*rl_shell(char *line_read);
t_ms		*ft_init_ms(t_ms *mini, char **envp);
void		setup_signal_handler(int flag);

// Other functions
char		*parse_variable(char *value);
void		trim_whitespace(char *str);

// Pipex functions
void		exec_commands(t_astnode *node, t_ms *ms);
char		*find_path(char *cmd, char **envp);
char		*quote_master(char quote);
int			char_counter(const char *str, char c);
void		exec_pipe(t_astnode *node);

// Args Mgmt
char		**filter_argv(char **argv, const char *target);
int			get_argc(char *argv[]);

//beta
int			setup_redirections(t_astnode *node);

//utils
t_env		*give_envp(char **envp, int flag);
t_env		*find_envp(char *variable, t_env *env);
int			if_is_local(char *cmd);

//void		sigint_handler(void);
char		*env_get_var(char *variable, t_env *env);
void		update_pwd(char *old_pwd, char *path, t_env *env);
char		*get_pwd(char *path, char *old_pwd);
void		check_path(char *path);
void		print_errors(char *str, int flag);
int			change_shlvl(t_env *env);
int			make_redirection(t_astnode *node);
int			env_add_var(char *var, t_env *env);
void		close_node_fd(t_astnode *node, int *pipefd);
t_ms		*give_mini(t_ms *mini_cpy, int copy);
// int			if_is_local(char *cmd);
void		handle_sigint_heredoc(int sig);
int			monitoring_hd_pipe(int *pipefd, t_lst_cmd *node, size_t i);
void		make_here_doc_pipe(int *pipefd, t_lst_cmd *node, size_t i);

//list for pwd
t_list		*lnew_node(char *name_value);
int			add_node(char *content, t_list *list);
void		delete_last_node(t_list *list);
void		free_list(t_list *env);

//execution for pipe
int			copy_ast_in_list(t_astnode *node, t_lst_cmd **head);
int			setup_redirections_pipe(t_lst_cmd *list);
int			make_redirection_pipe(t_lst_cmd *node);
int			is_local_fct_pipe(t_ms *mini, t_lst_cmd *list);
int			wait_pids(int pid, int flag);
void		cls_fd_pipe(t_lst_cmd *list, int *pipefd);
void		exec_command_pipe(t_lst_cmd *list, t_ms *ms);
void		free_cmd_list(t_lst_cmd *list);

#endif // MINISHELL_H
