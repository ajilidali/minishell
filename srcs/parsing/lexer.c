/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/06/04 14:37:52 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <ctype.h>
#include <string.h>

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	lexer_peek(Lexer *lexer)
{
	if (lexer->pos >= lexer->length)
		return ('\0');
	return (lexer->input[lexer->pos]);
}

void	lexer_advance(Lexer *lexer)
{
	lexer->pos++;
}

void	lexer_skip_whitespace(Lexer *lexer)
{
	while (is_whitespace(lexer_peek(lexer)))
		lexer_advance(lexer);
}

Token	lexer_word(Lexer *lexer)
{
	size_t	start;
	size_t	length;
	char	*value;
	Token	token;

	start = lexer->pos;
	while (!is_whitespace(lexer_peek(lexer)) && !is_operator(lexer_peek(lexer))
		&& !is_quote(lexer_peek(lexer)) && lexer_peek(lexer) != '\0')
		lexer_advance(lexer);
	length = lexer->pos - start;
	value = (char *)malloc(length + 1);
	ft_strncpy(value, lexer->input + start, length);
	value[length] = '\0';
	token.type = TOKEN_WORD;
	token.value = value;
	return (token);
}

/*Token	lexer_string(Lexer *lexer)
{
	char	quote_type;
	size_t	start;
	size_t	length;
	char	*value;
	char	*qc;
	Token	token;

	quote_type = lexer_peek(lexer);
	if (quote_counter(lexer->input, quote_type) % 2 != 0)
		qc = quote_master(quote_type);
	else
		qc = ft_strdup("");
	lexer_advance(lexer);
	start = lexer->pos;
	while (lexer_peek(lexer) != quote_type && lexer_peek(lexer) != '\0')
		lexer_advance(lexer);
	length = lexer->pos - start;
	value = (char *)malloc(length + 1);
	ft_strncpy(value, lexer->input + start, length);
	value[length] = '\0';
	lexer_advance(lexer);
	// token.type = TOKEN_STRING;
	token.type = TOKEN_WORD;
	token.value = ft_strjoin(value, qc);
	return (token);
}*/

Token lexer_string(Lexer *lexer)
{
	char quote_type;
	size_t start;
	char *value;
	char *qc;
	Token token;

	quote_type = lexer_peek(lexer);
	if (quote_counter(lexer->input, quote_type) % 2 != 0)
		qc = quote_master(quote_type);
	else
		qc = ft_strdup("");
	lexer_advance(lexer);
	start = lexer->pos;
	while (lexer_peek(lexer) != quote_type && lexer_peek(lexer) != '\0')
		lexer_advance(lexer);
	value = (char *)malloc(lexer->pos - start + 1);
	ft_strncpy(value, lexer->input + start, lexer->pos - start);
	value[lexer->pos - start] = '\0';
	lexer_advance(lexer);
	// token.type = TOKEN_STRING;
	token.type = TOKEN_WORD;
	token.value = ft_strjoin(value, qc);
	return (token);
}


Token	lexer_operator(Lexer *lexer)
{
	char	value[2] = {lexer_peek(lexer), '\0'};
	Token	token;

	lexer_advance(lexer);
	token.type = TOKEN_OPERATOR;
	token.value = ft_strdup(value);
	return (token);
}

Lexer	lexer_init(const char *input)
{
	Lexer	lexer;

	lexer.input = input;
	lexer.pos = 0;
	lexer.length = ft_strlen(input);
	return (lexer);
}

Token	lexer_next_token(Lexer *lexer)
{
	char	current;
		Token token;

	lexer_skip_whitespace(lexer);
	current = lexer_peek(lexer);
	if (current == '\0')
	{
		token.type = TOKEN_EOF;
		token.value = NULL;
		return (token);
	}
	if (is_operator(current))
		return (lexer_operator(lexer));
	if (is_quote(current))
		return (lexer_string(lexer));
	return (lexer_word(lexer));
}
