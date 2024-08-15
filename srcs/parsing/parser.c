/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:57:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:19:58 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Next  t_token
void	parser_advance(t_parser *parser)
{
	if (parser->current_token.value)
		ft_free(parser->current_token.value);
	parser->current_token = lexer_next_token(&parser->lexer);
}

char	*parse_variable(char *value)
{
	char	*cpy;

	if (ft_strcmp(value, "$") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(++value, "?") == 0)
		return (ft_itoa(give_mini(NULL, 0)->exit_code));
	cpy = env_get_var(value, give_envp(NULL, 0), false);
	if (!cpy)
		return (ft_strdup(NULL));
	return (ft_strdup(cpy));
}

t_astnode	*parse_pipeline(t_parser *parser)
{
	t_astnode	*left;
	t_astnode	*node;

	left = parse_command(parser);
	while (parser->current_token.type == TOKEN_PIPE
		&& ft_strcmp(parser->current_token.value, "|") == 0)
	{
		node = (t_astnode *)ft_malloc(sizeof(t_astnode));
		node->type = AST_PIPELINE;
		node->left = left;
		parser_advance(parser);
		node->right = parse_command(parser);
		left = node;
	}
	return (left);
}

// Free AST
void	free_ast(t_astnode *node)
{
	size_t	i;

	if (!node)
		return ;
	i = 0;
	if (node->type == AST_COMMAND)
	{
		while (i <= node->args_count - 1 && node->args_count > 0)
			ft_free(node->args[i++]);
		ft_free(node->args);
	}
	else if (node->type == AST_PIPELINE)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	ft_free(node);
}
