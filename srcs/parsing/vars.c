/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 20:21:14 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

Alias	*ft_init_alias(void)
{
	size_t	i;
	Alias	*aliases;

	i = 0;
	aliases = (Alias *)ft_malloc(sizeof(Alias) * 1024);
	if (!aliases)
	{
		ft_putendl_fd("Memory allocation error", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	while (i < 1024)
	{
		aliases[i].cmd = NULL;
		aliases[i].value = NULL;
		i++;
	}
	return (aliases);
}

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
	mini->alias_count = 0;
	mini->exit_code = 0;
	give_mini(mini, 1);
	return (mini);
}

t_astnode	*initialize_ast_node(void)
{
	t_astnode	*node;

	node = (t_astnode *)ft_malloc(sizeof(t_astnode));
	node->type = AST_COMMAND;
	node->left = node->right = NULL;
	node->args = (char **)ft_malloc(MAX_ARGS * sizeof(char *));
	node->redirections = (t_redirection *)ft_malloc(MAX_REDIRS * sizeof(t_redirection));
	node->args_capacity = MAX_ARGS;
	node->redirections_capacity = MAX_REDIRS;
	node->args_count = 0;
	node->redirections_count = 0;
	return (node);
}