/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/06/06 18:54:20 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <ctype.h>
#include <string.h>

int	is_pipe(char c)
{
	return (c == '|');
}

int	is_dollar(char c)
{
	return (c == '$');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '&' || c == ';' || c == '<' || c == '>');
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

char	*copy_except_first_n_chars(const char *input, size_t n)
{
	char	*result;
	size_t	len;

	if (input == NULL)
	{
		result = (char *)malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	len = strlen(input);
	if (len <= n)
	{
		result = (char *)malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	result = (char *)malloc(len - n + 1);
	if (result == NULL)
		return (NULL);
	strcpy(result, input + n);
	return (result);
}

Token	lexer_dollar(Lexer *lexer)
{
	size_t	start;
	char	*value;
	Token	token;
	t_env	*cpy;

	start = lexer->pos;
	while (!is_whitespace(lexer_peek(lexer)) 
		&& !is_operator(lexer_peek(lexer))
		&& !is_quote(lexer_peek(lexer)) 
		&& !is_pipe(lexer_peek(lexer))
		&& is_dollar(lexer_peek(lexer)) 
		&& lexer_peek(lexer) != '\0')
		lexer->pos++;
	token.type = TOKEN_WORD;
	value = copy_except_first_n_chars(lexer->input + start, 1);
	cpy = find_envp(value, give_envp(NULL, 0));
	if (!cpy)
	{
		token.value = value;
		return (token);
	}
	lexer->pos += ft_strlen(value);
	return ((token.value = copy_except_first_n_chars(cpy->name_value,
				ft_strlen(value) + 1)), token);
}

Token	lexer_word(Lexer *lexer)
{
	size_t	start;
	size_t	length;
	char	*value;
	Token	token;

	start = lexer->pos;
	while (!is_whitespace(lexer_peek(lexer)) 
		&& !is_operator(lexer_peek(lexer))
		&& !is_quote(lexer_peek(lexer)) 
		&& !is_pipe(lexer_peek(lexer))
		&& lexer_peek(lexer) != '\0')
		lexer->pos++;
	length = lexer->pos - start;
	value = (char *)malloc(length + 1);
	ft_strncpy(value, lexer->input + start, length);
	value[length] = '\0';
	token.type = TOKEN_WORD;
	token.value = value;
	return (token);
}

Token	lexer_string(Lexer *lexer)
{
	char	quote_type;
	size_t	start;
	char	*value;
	char	*qc;
	Token	token;

	quote_type = lexer_peek(lexer);
	if (quote_counter(lexer->input, quote_type) % 2 != 0)
		qc = quote_master(quote_type);
	else
		qc = ft_strdup("");
	lexer->pos++;
	start = lexer->pos;
	while (lexer_peek(lexer) != quote_type && lexer_peek(lexer) != '\0')
		lexer->pos++;
	value = (char *)malloc(lexer->pos - start + 1);
	ft_strncpy(value, lexer->input + start, lexer->pos - start);
	value[lexer->pos - start] = '\0';
	lexer->pos++;
	// token.type = TOKEN_STRING;
	token.type = TOKEN_WORD;
	token.value = ft_strjoin(value, qc);
	return (token);
}

Token	lexer_operator(Lexer *lexer)
{
	char	value[2];
	Token	token;

	value[0] = lexer_peek(lexer);
	value[1] = '\0';
	lexer->pos++;
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

Token	lexer_pipe(Lexer *lexer)
{
	char	value[2];
	Token	token;

	value[0] = lexer_peek(lexer);
	value[1] = '\0';
	lexer->pos++;
	token.type = TOKEN_PIPE;
	token.value = ft_strdup(value);
	return (token);
}

Token	lexer_next_token(Lexer *lexer)
{
	char	current;
	Token	token;

	while (is_whitespace(lexer_peek(lexer)))
		lexer->pos++;
	current = lexer_peek(lexer);
	if (current == '\0')
	{
		token.type = TOKEN_EOF;
		token.value = NULL;
		return (token);
	}
	if (is_dollar(current))
		return (lexer_dollar(lexer));
	else if (is_pipe(current))
		return (lexer_pipe(lexer));
	else if (is_operator(current))
		return (lexer_operator(lexer));
	else if (is_quote(current))
		return (lexer_string(lexer));
	return (lexer_word(lexer));
}
