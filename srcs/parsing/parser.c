/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:57:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/04 16:15:57 by hclaude          ###   ########.fr       */
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
	char	*cpy;

	//value = ft_strdup(&value[1]); // pardon?!!
	cpy = env_get_var(++value, give_envp(NULL, 0));
	if (!cpy)
	{
		// value = ft_strdup(NULL); // ahah tu as avalé un clown -_-
		return (NULL);
	}
	return (ft_strdup(cpy)); // faut se calmer avec les strdup!!!!!
}

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
	size_t	i;

	if (!node)
		return ;
	i = 0;
	if (node->type == AST_COMMAND)
	{
        while (i <= node->args_count-1  && node->args_count > 0)
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
