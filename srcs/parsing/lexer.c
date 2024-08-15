/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/08/15 14:18:45 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	lexer_dollar(t_lexer *lexer)
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
	return (token_init(TOKEN_VARIABLE, value));
}

t_token	lexer_word(t_lexer *lex)
{
	size_t	init;
	int		in_quotes;
	char	current_quote;

	in_quotes = 0;
	current_quote = '\0';
	init = lex->pos;
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
	return (token_init(TOKEN_WORD, ext_val(lex->input, init, lex->pos - init)));
}

t_token	lexer_string(t_lexer *lexer)
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
			token_init(TOKEN_EMPTY, NULL));
	if (is_all_spaces(value))
		return (token_init(TOKEN_WORD, NULL));
	else if (quote_type != '\'')
		return (token_init(TOKEN_WORD, replace_variables(value)));
	return (token_init(TOKEN_WORD, value));
}

t_token	lexer_operator(t_lexer *lexer)
{
	char	current;
	char	value[3];

	current = lp(lexer);
	if (current == '<' || current == '>')
	{
		if (lexer->input[lexer->pos + 1] == current)
		{
			lexer->pos++;
			ft_memcpy(value, (char []){current, current, '\0'}, sizeof(value));
			lexer->pos++;
			return (token_init(TOKEN_OPERATOR, ft_strdup(value)));
		}
	}
	ft_memcpy(value, (char []){current, '\0'}, sizeof(value));
	lexer->pos++;
	return (token_init(TOKEN_OPERATOR, ft_strdup(value)));
}

t_token	lexer_pipe(t_lexer *lexer)
{
	char	value[2];

	value[0] = lp(lexer);
	value[1] = '\0';
	lexer->pos++;
	return (token_init(TOKEN_PIPE, ft_strdup(value)));
}
