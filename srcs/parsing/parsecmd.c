/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:11:26 by moajili           #+#    #+#             */
/*   Updated: 2024/08/11 20:39:54 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

int check_ast_for_errors(ASTNode *node)
{
	int left_error;
	int right_error;

	if (node == NULL)
		return (0);
	if (node->type == AST_ERR)
		return (1);
	left_error = check_ast_for_errors(node->left);
	right_error = check_ast_for_errors(node->right);
	return (left_error || right_error);
}

static ASTNode	*initialize_ast_node()
{
	ASTNode	*node;

	node = (ASTNode *)ft_malloc(sizeof(ASTNode));
	node->type = AST_COMMAND;
	node->left = node->right = NULL;
	node->args = (char **)ft_malloc(MAX_ARGS * sizeof(char *));
	node->redirections = (t_redirection *)ft_malloc(MAX_REDIRS * sizeof(t_redirection));
	node->args_capacity = MAX_ARGS;
	node->redirections_capacity = MAX_REDIRS;
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
			ft_free(node->redirections);
		node->redirections = (t_redirection *)ft_malloc(node->redirections_capacity * sizeof(t_redirection));
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
		node->type = AST_ERR;
		give_mini(NULL,0)->exit_code = 1;
	}
}

static void handle_argument(Parser *parser, ASTNode *node)
{
	if (node->args_count >= node->args_capacity)
	{
		node->args_capacity *= 2;
		if (node->args)
			ft_free(node->args);
		node->args = (char **)ft_malloc(node->args_capacity * sizeof(char *));
	}
	if (parser->current_token.type == TOKEN_VARIABLE)
		node->args[node->args_count++] = parse_variable(parser->current_token.value);
	else
		node->args[node->args_count++] = ft_strdup(parser->current_token.value);
	parser_advance(parser);
}

ASTNode *parse_command(Parser *parser)// Memory allocation failure
{
	ASTNode *node;

	node = initialize_ast_node();
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
