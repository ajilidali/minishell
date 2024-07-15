/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/07/15 11:44:03 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

static ASTNode	*initialize_ast_node()
{
	ASTNode	*node = (ASTNode *)malloc(sizeof(ASTNode));

	node->type = AST_COMMAND;
	node->left = node->right = NULL;
	node->args = (char **)malloc(10 * sizeof(char *));
	node->redirections = (t_redirection *)malloc(5 * sizeof(t_redirection));
	node->args_capacity = 10;
	node->redirections_capacity = 5;
	node->args_count = 0;
	node->redirections_count = 0;
	return node;
}

int type_of_redirect(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (FD_OUT);
	if (!ft_strcmp(str, ">>"))
		return (FD_ADDOUT);
	if (!ft_strcmp(str, "<"))
		return (FD_IN);
	return (FD_HD);
}

static void handle_redirection(Parser *parser, ASTNode *node)
{
	if (node->redirections_count >= node->redirections_capacity)
	{
		node->redirections_capacity *= 2;
		if (node->redirections)
			free(node->redirections);
		node->redirections = (t_redirection *)malloc(node->redirections_capacity * sizeof(t_redirection));
	}
	node->redirections[node->redirections_count].flag = type_of_redirect(parser->current_token.value);
	parser_advance(parser);
	if (parser->current_token.type == TOKEN_EMPTY)
		parser_advance(parser);
	else if (parser->current_token.type == TOKEN_WORD)
	{
		node->redirections[node->redirections_count].file = ft_strdup(parser->current_token.value);
		node->redirections_count++;
		parser_advance(parser);
	}
	else
	{
		print_errors(NULL, ER_REDIRECT_ERROR); // Proubleme ici
		parser_advance(parser);
		//exit(1);
	}
}

static void handle_argument(Parser *parser, ASTNode *node)
{
	if (node->args_count >= node->args_capacity)
	{
		node->args_capacity *= 2;
		if (node->args)
			free(node->args);
		node->args = (char **)malloc(node->args_capacity * sizeof(char *));
	}
	if (parser->current_token.type == TOKEN_VARIABLE)
		node->args[node->args_count++] = parse_variable(parser->current_token.value);
	else
		node->args[node->args_count++] = ft_strdup(parser->current_token.value);
	parser_advance(parser);
}

ASTNode *parse_command(Parser *parser)// Memory allocation failure
{
	ASTNode *node = initialize_ast_node();

	while (parser->current_token.type == TOKEN_WORD ||
			parser->current_token.type == TOKEN_VARIABLE ||
			parser->current_token.type == TOKEN_OPERATOR)
	{
		if (parser->current_token.type == TOKEN_OPERATOR && is_redirection(parser->current_token.value[0]))
			handle_redirection(parser, node);
		else
			handle_argument(parser, node);
	}
	node->args[node->args_count] = NULL;
	return (node);
}
