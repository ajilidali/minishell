/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/25 17:52:16 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <sys/types.h>

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
	return (copy_except_first_n_chars(cpy->name_value, ft_strlen(value) + 1));
}

/*ASTNode *parse_command(Parser *parser)
{
    ASTNode *node;
    size_t capacity, redir_capacity;
    size_t count, redir_count;

    node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_COMMAND;
    node->left = node->right = NULL;
    capacity = 10;
    redir_capacity = 5;
    count = redir_count = 0;
    node->args = (char **)malloc(capacity * sizeof(char *));
    node->redirections = (t_redirection *)malloc(redir_capacity * sizeof(t_redirection));

    while (parser->current_token.type == TOKEN_WORD ||
           parser->current_token.type == TOKEN_VARIABLE ||
           parser->current_token.type == TOKEN_OPERATOR)
    {
        if (parser->current_token.type == TOKEN_OPERATOR && is_redirection(parser->current_token.value[0]))
        {
            // Handle redirections
            if (redir_count >= redir_capacity)
            {
                redir_capacity *= 2;
                node->redirections = (t_redirection *)realloc(node->redirections, redir_capacity * sizeof(t_redirection));
            }
            node->redirections[redir_count].type = ft_strdup(parser->current_token.value);
            parser_advance(parser);
            if (parser->current_token.type == TOKEN_WORD)
            {
                node->redirections[redir_count].file = ft_strdup(parser->current_token.value);
                redir_count++;
                parser_advance(parser);
            }
            else
            {
                printf("Syntax error: expected file after redirection\n");
                exit(1);
            }
        }
        else
        {
            if (count >= capacity)
            {
                capacity *= 2;
                node->args = (char **)realloc(node->args, capacity * sizeof(char *));
            }
            if (parser->current_token.type == TOKEN_VARIABLE)
                node->args[count++] = parse_variable(parser->current_token.value);
            else
                node->args[count++] = ft_strdup(parser->current_token.value);
            parser_advance(parser);
        }
    }
    node->args[count] = NULL;
    node->redirection_count = redir_count;
    return node;
}*/

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
void free_ast(ASTNode *node)
{
    int i;

    if (!node)
        return;
    i = 0;
    if (node->type == AST_COMMAND)
    {
        while(node->args[i])
            free(node->args[i++]);
        free(node->args);
    }
    else if (node->type == AST_PIPELINE)
    {
        free_ast(node->left);
        free_ast(node->right);
    }
    free(node);
}
