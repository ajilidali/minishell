/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/06/06 22:26:16 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <ctype.h>
#include <stdio.h>
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

Token lexer_dollar(Lexer *lexer)
{
    size_t	start;
    size_t	length;
    char	*value;
    Token	token;
    start = lexer->pos;
    lexer->pos++;
    while (isalnum(lexer_peek(lexer)) || lexer_peek(lexer) == '_')
        lexer->pos++;
    length = lexer->pos - start;
    value = (char *)malloc(length + 1);
    ft_strncpy(value, lexer->input + start, length);
    value[length] = '\0';
    token.type = TOKEN_VARIABLE;
    token.value = value;
    return (token);
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
	//printf("lexer lenght :%zu\n",lexer->length);
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
	printf("value : %s\n",value);
	// token.type = TOKEN_STRING;
	token.type = TOKEN_WORD;
	token.value = ft_strjoin(value, qc);
	printf("tok : %s\n",token.value);
	return (token);
}


Token lexer_operator(Lexer *lexer)
{
    Token token;
    char current = lexer_peek(lexer);

    if (current == '<' || current == '>')
    {
        lexer->pos++;
        if (lexer_peek(lexer) == current) // Check for << or >>
        {
            char value[3] = {current, current, '\0'};
            lexer->pos++;
            token.type = TOKEN_OPERATOR;
            token.value = ft_strdup(value);
            return (token);
        }
    }

    char value[2] = {current, '\0'};
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
	//printf("%s\n",lexer->input);
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
