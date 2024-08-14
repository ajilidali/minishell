/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 11:18:46 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <string.h>

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '&' || c == ';' || c == '<' || c == '>');
}

char	lp(Lexer *lexer)
{
	if (lexer->pos >= lexer->length)
		return ('\0');
	return (lexer->input[lexer->pos]);
}

Token	crt_tkn(TokenType type, char *value)
{
	Token	token;

	token.type = type;
	token.value = value;
	return (token);
}

Token	lexer_dollar(Lexer *lexer)
{
	size_t	start;
	size_t	length;
	char	*value;

	start = lexer->pos;
	lexer->pos++;
	while ((ft_isalnum(lp(lexer)) || lp(lexer) == '_' || lp(lexer) == '?')
		&& (lp(lexer) != ' '))
		lexer->pos++;
	length = lexer->pos - start;
	value = allocate_string(length + 1);
	ft_strncpy(value, lexer->input + start, length);
	return (crt_tkn(TOKEN_VARIABLE, value));
}

char	*ext_val(const char *input, size_t start, size_t len)
{
	char	*value;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	value = allocate_string(len + 1);
	while (i < len)
	{
		if (input[start + i] != '\'' && input[start + i] != '\"')
			value[j++] = input[start + i];
		i++;
	}
	return (value);
}

Token	lexer_word(Lexer *lex)
{
	size_t	start;
	int		in_quotes;
	char	current_quote;

	in_quotes = 0;
	current_quote = '\0';
	start = lex->pos;
	while (lp(lex) != '\0' && lp(lex) != '|')
	{
		if (!in_quotes && is_whitespace(lp(lex)))
			break ;
		if (in_quotes && lp(lex) == current_quote && (lp(lex) == '\''
				|| lp(lex) == '\"'))
		{
			in_quotes = 0;
			current_quote = '\0';
		}
		else if (!in_quotes && (lp(lex) == '\'' || lp(lex) == '\"'))
		{
			in_quotes = 1;
			current_quote = lp(lex);
		}
		lex->pos++;
	}
	return (crt_tkn(TOKEN_WORD, ext_val(lex->input, start, lex->pos - start)));
}

char	*replace_variables(char *in)
{
	char	*result;
	char	*final;
	int		start;
	size_t		i;

	i = 0;
	if (!in)
		return (NULL);
	if (char_counter(in, '$') == 0)
		return (in);
	while (in[i] && in[i] != '$')
		i++;
	start = i;
	if (i < ft_strlen(in) && in[i] == '$')
	{
		if (in[i + 1] == ' ' || in[i + 1] == '\0')
			return (in);
		i++;
		while (i < ft_strlen(in) && (in[i] == '?' || in[i] == '_'
				|| ft_isalnum(in[i])))
			i++;
	}
	else
	{
		start = 0;
		i = ft_strlen(in);
	}
	result = allocate_string((i - start) + 1);
	ft_strncpy(result, &in[start], i - start);
	if (!result)
		return (ft_free(result), NULL);
	final = ft_replace(in, result, parse_variable(result));
	if (char_counter(in, '$') != 0)
		return (replace_variables(final));
	return (ft_free(in), ft_free(result), final);
}

int	is_all_spaces(const char *str)
{
	int	i;

	if (str[0] == '\0')
	{
		return (1);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

Token	lexer_string(Lexer *lexer)
{
	char	quote_type;
	size_t	start;
	char	*value;

	quote_type = lp(lexer);
	lexer->pos++;
	start = lexer->pos;
	while (lp(lexer) != quote_type && lp(lexer) != '\0')
		lexer->pos++;
	if (char_counter(lexer->input, quote_type) % 2 == 0)
	{
		value = allocate_string(lexer->pos - start + 1);
		ft_strncpy(value, lexer->input + start, lexer->pos - start);
	}
	else
		return (print_errors("Quotes must be terminated", ER_SYNTAX_ERROR),
			crt_tkn(TOKEN_EMPTY, NULL));
	if (is_all_spaces(value))
		return (crt_tkn(TOKEN_EMPTY, NULL));
	else if (quote_type != '\'')
		return (crt_tkn(TOKEN_WORD, replace_variables(value)));
	return (crt_tkn(TOKEN_WORD, value));
}

Token	lexer_operator(Lexer *lexer)
{
	char	current;
	char	value[3];

	current = lp(lexer);
	if (current == '<' || current == '>')
	{
		if (lexer->input[lexer->pos + 1] == current)
		{
			lexer->pos++;
			ft_memcpy(value, (char[]){current, current, '\0'}, sizeof(value));
			lexer->pos++;
			return (crt_tkn(TOKEN_OPERATOR, ft_strdup(value)));
		}
	}
	ft_memcpy(value, (char[]){current, '\0'}, sizeof(value));
	lexer->pos++;
	return (crt_tkn(TOKEN_OPERATOR, ft_strdup(value)));
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

	value[0] = lp(lexer);
	value[1] = '\0';
	lexer->pos++;
	token.type = TOKEN_PIPE;
	token.value = ft_strdup(value);
	return (token);
}

Token	lexer_next_token(Lexer *lexer)
{
	char	current;

	while (is_whitespace(lp(lexer)))
		lexer->pos++;
	current = lp(lexer);
	if (current == '\0')
		return (crt_tkn(TOKEN_EOF, NULL));
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
