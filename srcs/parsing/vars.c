/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/08/15 14:20:19 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ms	*ft_init_ms(t_ms *mini, char **envp)
{
	mini = ft_malloc(sizeof(t_ms));
	if (mini == NULL)
		return (NULL);
	mini->lexer.input = NULL;
	mini->lexer.pos = 0;
	mini->lexer.length = 0;
	mini->token.type = TOKEN_EOF;
	mini->token.value = NULL;
	mini->env = give_envp(envp, COPY);
	if (!mini->env)
		return (NULL);
	mini->parser.lexer = mini->lexer;
	mini->parser.current_token = mini->token;
	mini->ast = NULL;
	mini->line = NULL;
	mini->exit_code = 0;
	give_mini(mini, 1);
	return (mini);
}

t_astnode	*initialize_ast_node(void)
{
	t_astnode	*node;

	node = (t_astnode *)ft_malloc(sizeof(t_astnode));
	node->type = AST_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->args = (char **)ft_malloc(MAX_ARGS * sizeof(char *));
	node->redirections = (t_redirection *)ft_malloc(
			MAX_REDIRS * sizeof(t_redirection));
	node->args_capacity = MAX_ARGS;
	node->redirections_capacity = MAX_REDIRS;
	node->args_count = 0;
	node->redirections_count = 0;
	return (node);
}

t_parser	parser_init(const char *input)
{
	t_parser	parser;

	parser.lexer = lexer_init(input);
	parser.current_token = lexer_next_token(&parser.lexer);
	return (parser);
}

t_lexer	lexer_init(const char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.pos = 0;
	lexer.length = ft_strlen(input);
	return (lexer);
}

t_token	token_init(t_token_type type, char *value)
{
	t_token	token;

	token.type = type;
	token.value = value;
	return (token);
}
