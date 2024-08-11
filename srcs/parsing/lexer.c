/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/08/11 12:09:37 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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

Token	create_token(TokenType type, char *value)
{
	Token	token;
	token.type = type;
	token.value = value;
	return token;
}

Token lexer_dollar(Lexer *lexer)
{
	size_t	start;
	size_t	length;
	char	*value;

	start = lexer->pos;
	lexer->pos++;
	while (ft_isalnum(lexer_peek(lexer)) || lexer_peek(lexer) == '_' || lexer_peek(lexer) == '?')
		lexer->pos++;
	length = lexer->pos - start;
    value = allocate_string(length + 1);
	ft_strncpy(value, lexer->input + start, length);
    return create_token(TOKEN_VARIABLE, value);
}

char* extract_value(const char *input, size_t start, size_t len)
{
    char *value;
    size_t i;
	size_t j;

	i = 0;
	j = 0;
	value = allocate_string(len + 1);
    while (i < len)
        if (input[start + i] != '\'' && input[start + i] != '\"')
            value[j++] = input[start + i++];
    return value;
}

Token lexer_word(Lexer *lexer)
{
    size_t start;
    int inside_quotes;
    char current_quote;
	char *value;
	
	start = lexer->pos;
	inside_quotes = 0;
	current_quote = '\0';
    while (lexer_peek(lexer) != '\0' && (inside_quotes || !is_whitespace(lexer_peek(lexer))))
    {
        if (lexer_peek(lexer) == '\'' || lexer_peek(lexer) == '\"')
        {
            if (inside_quotes && lexer_peek(lexer) == current_quote)
            {
                inside_quotes = 0;
                current_quote = '\0';
            }
            else if (!inside_quotes)
            {
                inside_quotes = 1;
                current_quote = lexer_peek(lexer);
            }
        }
        lexer->pos++;
    }
    value = extract_value(lexer->input, start, lexer->pos - start);
    if (current_quote != '\'')
        return create_token(TOKEN_WORD, replace_variables(value));
    return create_token(TOKEN_WORD, value);
}


char *replace_variables(char *input)
{
	char *result;
	char *final;
	int start;
	int i = 0;
	int end;
	
	if (!input)
		return NULL;
	if (char_counter(input,'$') == 0)
		return (input);
	while (input[i] && input[i] != '$')
		i++;
	start = i;
	if (i < (int)ft_strlen(input) && input[i] == '$')
	{
		i++;
		while (i < (int)ft_strlen(input) && (input[i] == '?' || input[i] == '_' || ft_isalnum(input[i])))
			i++;
		end = i;
	} else
    {
		start = 0;
		end = ft_strlen(input);
	}
    result = allocate_string((end - start) + 1);
	ft_strncpy(result, &input[start], end - start);
	if (!result)
		return (free(result),NULL);
	final = ft_replace(input,result,parse_variable(result));
	if (char_counter(input,'$') != 0)
		return (replace_variables(final));
	free(input);
	free(result);
	return (final);
}

Token	lexer_string(Lexer *lexer)
{
	char	quote_type;
	size_t	start;
	char	*value;

	quote_type = lexer_peek(lexer);
	lexer->pos++;
	start = lexer->pos;
	while (lexer_peek(lexer) != quote_type && lexer_peek(lexer) != '\0')
		lexer->pos++;
	if (char_counter(lexer->input, quote_type) % 2 == 0)
	{
        value = allocate_string(lexer->pos - start + 1);
		ft_strncpy(value, lexer->input + start, lexer->pos - start);
	}
	else
        return (print_errors(NULL, ER_SYNTAX_ERROR),create_token(TOKEN_EMPTY, NULL));
    if (quote_type != '\'')
        return(create_token(TOKEN_WORD, replace_variables(value)));
    return (create_token(TOKEN_WORD,value));
}

Token	lexer_operator(Lexer *lexer)
{
	char	current;
    char    value[3];

	current = lexer_peek(lexer);
	if (current == '<' || current == '>')
	{
		if (lexer->input[lexer->pos+1] == current) // Check for << or >>
		{
			lexer->pos++;
            ft_memcpy(value, (char[]){current, current, '\0'}, sizeof(value));
			lexer->pos++;
            return(create_token(TOKEN_OPERATOR,ft_strdup(value)));
		}
	}
    ft_memcpy(value, (char[]){current, '\0', '\0'}, sizeof(value));
	lexer->pos++;
    return(create_token(TOKEN_OPERATOR,ft_strdup(value)));
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

    ft_memcpy(value, (char[]){lexer_peek(lexer), '\0'}, sizeof(value));
	lexer->pos++;
    return(create_token(TOKEN_PIPE, ft_strdup(value)));
}

Token	lexer_next_token(Lexer *lexer)
{
	char	current;

	while (is_whitespace(lexer_peek(lexer)))
		lexer->pos++;
	current = lexer_peek(lexer);
	if (current == '\0')
        return(create_token(TOKEN_EOF,NULL));
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
