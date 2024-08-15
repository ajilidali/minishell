/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 22:00:08 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 22:03:39 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_operator(char c)
{
	return (c == '&' || c == ';' || c == '<' || c == '>');
}

t_token	lexer_next_token(t_lexer *lexer)
{
	char	current;

	while (is_whitespace(lp(lexer)))
		lexer->pos++;
	current = lp(lexer);
	if (current == '\0')
		return (token_init(TOKEN_EOF, NULL));
	if (current == '$')
		return (lexer_dollar(lexer));
	else if (current == '|')
		return (lexer_pipe(lexer));
	else if (is_operator(current))
		return (lexer_operator(lexer));
	else if (current == '"' || current == '\'')
		return (lexer_string(lexer));
	return (lexer_word(lexer));
}

char	lp(t_lexer *lexer)
{
	if (lexer->pos >= lexer->length)
		return ('\0');
	return (lexer->input[lexer->pos]);
}
