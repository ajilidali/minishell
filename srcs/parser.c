/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/06/03 14:10:10 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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
	while (parser->current_token.type == TOKEN_WORD)
	{
		if (count >= capacity)
		{
			capacity *= 2;
			free(node->args);
			node->args = (char **)malloc(capacity * sizeof(char *));
		}
		node->args[count++] = ft_strdup(parser->current_token.value);
		parser_advance(parser);
	}
	node->args[count] = NULL;
	return (node);
}

// Pipe parsing
ASTNode	*parse_pipeline(Parser *parser)
{
	ASTNode	*left;
	ASTNode	*node;

	left = parse_command(parser);
	while (parser->current_token.type == TOKEN_PIPE
		&& strcmp(parser->current_token.value, "|") == 0)
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
void	execute_ast(ASTNode *node)
{
	int	pipefd[2];

	if (!node)
		return ;
	if (node->type == AST_COMMAND)
	{
		if (is_local_fct(node) == 0)
			return ;
		if (fork() == 0)
		{
			if (execute(node, g_ms.envp) != 0)
				return (printf("DEDSEC: %s: command not found\n", node->args[0]),exit(1));
		}
		else
			wait(NULL);
	}
	else if (node->type == AST_PIPELINE)
	{
		pipe(pipefd);
		ft_fork_left(node->left, pipefd);
		ft_fork_right(node->right, pipefd);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
		wait(NULL);
	}
}

// Pipe --> Right
void	ft_fork_right(ASTNode *node, int pipefd[2])
{
	if (fork() == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node);
		exit(0);
	}
}

// Pipe --> Left
void	ft_fork_left(ASTNode *node, int pipefd[2])
{
	if (fork() == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node);
		exit(0);
	}
}
