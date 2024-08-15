/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:25 by moajili           #+#    #+#             */
/*   Updated: 2024/08/15 14:31:44 by hclaude          ###   ########.fr       */
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
}	t_pidl;

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

//t_lexer Structs
typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_EMPTY,
	TOKEN_STRING,
	TOKEN_VARIABLE,
	TOKEN_PIPE,
	TOKEN_OPERATOR,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_lexer
{
	const char	*input;
	size_t		pos;
	size_t		length;
}	t_lexer;

//Abstract Syntax Tree Structs
typedef enum s_astnode_type
{
	AST_COMMAND,
	AST_PIPELINE,
	AST_ERR
}	t_astnode_type;

typedef struct s_astnode
{
	t_astnode_type		type;
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

// t_parser Structs
typedef struct s_parser
{
	t_lexer	lexer;
	t_token	current_token;
}	t_parser;

// Minishell Structs
typedef struct s_ms
{
	t_lexer		lexer;
	t_token		token;
	t_parser	parser;
	t_astnode	*ast;
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
int			run_exit(char **command, t_ms *mini);

// Env functions
void		free_env(t_env *env);
char		**get_tabenv(t_env *env);
t_env		*copy_env(char **envp);
t_env		*new_node(char *name_value, bool hide);
t_env		*create_empty_env(void);

// Idea : make a structure for builtins and then strcmp in vars:44 in a while,
// have to make sure can run fcts from structs

// Is functions
int			is_whitespace(char c);

// t_token assigning functions
t_token		lexer_operator(t_lexer *lexer);
t_token		lexer_word(t_lexer *lexer);
t_token		lexer_pipe(t_lexer *lexer);
t_token		lexer_dollar(t_lexer *lexer);
t_token		lexer_string(t_lexer *lexer);
char		*replace_variables(char *in);
t_token		token_init(t_token_type type, char *value);

// t_lexer functions
t_token		lexer_next_token(t_lexer *lexer);
t_lexer		lexer_init(const char *input);
char		lp(t_lexer *lexer);

// AST & t_parser functions
t_parser	parser_init(const char *input);
void		parser_advance(t_parser *parser);
t_astnode	*parse_command(t_parser *parser);
t_astnode	*parse_pipeline(t_parser *parser);
void		free_ast(t_astnode *node);
int			check_ast_for_errors(t_astnode *node);

// Main functions
char		*rl_shell(char *line_read);
t_ms		*ft_init_ms(t_ms *mini, char **envp);
void		setup_signal_handler(int flag);

// Other functions
char		*parse_variable(char *value);

// Pipex functions
void		exec_commands(t_astnode *node, t_ms *ms);
char		*find_path(char *cmd, char **envp);
char		*quote_master(char quote);
int			char_counter(const char *str, char c);
void		exec_pipe(t_astnode *node);

// Args Mgmt
char		**filter_argv(char **argv, const char *target);
int			get_argc(char *argv[]);
t_astnode	*initialize_ast_node(void);
//beta
int			setup_redirections(t_astnode *node);

//utils
t_env		*give_envp(char **envp, int flag);
t_env		*find_envp(char *variable, t_env *env, bool flag);
int			is_all_spaces(const char *str);
char		*ext_val(const char *input, size_t start, size_t len);
char		*env_get_var(char *variable, t_env *env, bool flag);
void		update_pwd(char *old_pwd, t_env *env);
char		*get_pwd(char *path, char *old_pwd);
void		check_path(char *path);
void		print_errors(char *str, int flag);
int			change_shlvl(t_env *env);
int			make_redirection(t_astnode *node);
int			env_add_var(char *var, t_env *env, bool hide);
void		close_node_fd(t_astnode *node, int *pipefd);
t_ms		*give_mini(t_ms *mini_cpy, int copy);
int			if_is_local(char *cmd);
void		handle_sigint_heredoc(int sig);
int			monitoring_hd_pipe(int *pipefd, t_lst_cmd *node, size_t i);
void		make_here_doc_pipe(int *pipefd, t_lst_cmd *node, size_t i);
int			is_pwd(t_env *env);
int			is_oldpwd(t_env *env);

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
