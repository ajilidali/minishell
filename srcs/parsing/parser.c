/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/06/06 23:02:20 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

Parser	parser_init(const char *input)
{
	Parser	parser;

	parser.lexer = lexer_init(input);
	parser.current_token = lexer_next_token(&parser.lexer);
	return (parser);
}

// Next  Token
void	parser_advance(Parser *parser)
{
	if (parser->current_token.value)
		free(parser->current_token.value);
	parser->current_token = lexer_next_token(&parser->lexer);
}

char	*parse_variable(char *value)
{
	t_env	*cpy;

	value = copy_except_first_n_chars(value, 1);
	cpy = find_envp(value, give_envp(NULL, 0));
	if (!cpy)
	{
		value = "";
		return (value);
	}
	return (copy_except_first_n_chars(cpy->name_value,ft_strlen(value) + 1));
}

// Parse the command
ASTNode	*parse_command(Parser *parser)
{
	ASTNode	*node;
	size_t	capacity;
	size_t	count;

	node = (ASTNode *)malloc(sizeof(ASTNode));
	node->type = AST_COMMAND;
	node->left = node->right = NULL;
	capacity = 10;
	count = 0;
	node->args = (char **)malloc(capacity * sizeof(char *));
	while (parser->current_token.type == TOKEN_WORD || parser->current_token.type == TOKEN_VARIABLE)
	{
		if (count >= capacity)
		{
			capacity *= 2;
			free(node->args);
			node->args = (char **)malloc(capacity * sizeof(char *));
		}
		if (parser->current_token.type == TOKEN_VARIABLE)
		   	node->args[count++] = parse_variable(parser->current_token.value);
		else
			node->args[count++] = ft_strdup(parser->current_token.value);
		parser_advance(parser);
	}
	return (node->args[count] = NULL,node);
}

// Pipe parsing
ASTNode	*parse_pipeline(Parser *parser)
{
	ASTNode	*left;
	ASTNode	*node;

	left = parse_command(parser);
	while (parser->current_token.type == TOKEN_PIPE
		&& ft_strcmp(parser->current_token.value, "|") == 0)
	{
		node = (ASTNode *)malloc(sizeof(ASTNode));
		node->type = AST_PIPELINE;
		node->left = left;
		parser_advance(parser);
		node->right = parse_command(parser);
		left = node;
	}
	return (left);
}

// Free AST
void	free_ast(ASTNode *node)
{
	char	**arg;

	if (!node)
		return ;
	if (node->type == AST_COMMAND)
	{
		arg = node->args;
		while (*arg)
		{
			free(*arg);
			arg++;
		}
		free(node->args);
	}
	else if (node->type == AST_PIPELINE)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	free(node);
}

// AST Execution
void	execute_ast(ASTNode *node, MS *mini)
{
	int	pipefd[2];

	if(!node)
		return;
	if (node->type == AST_COMMAND)
	{
		node->args = filter_argv(get_argc(node->args),node->args, "");
		if (is_local_fct(mini, node) == 0)
			return ;
		if (fork() == 0 && execute(node, get_tabenv(mini->envp)) != 0)
		{
				ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
				ft_putstr_fd(node->args[0], STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				exit(1);
		}
		else
			wait(NULL);
	}
	else if (node->type == AST_PIPELINE)
	{
		pipe(pipefd);
		ft_fork_left(node->left, mini, pipefd);
		ft_fork_right(node->right, mini, pipefd);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
		wait(NULL);
	}
}

// Pipe --> Right
void	ft_fork_right(ASTNode *node, MS *mini, int pipefd[2])
{
	if (fork() == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node, mini);
		exit(0);
	}
}

// Pipe --> Left
void	ft_fork_left(ASTNode *node, MS *mini, int pipefd[2])
{
	if (fork() == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node, mini);
		exit(0);
	}
}