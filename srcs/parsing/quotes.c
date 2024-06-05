/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/06/05 08:35:47 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int quote_counter(const char *str, char quote)
{
	int count;
	int len;

	count = 0;
	len = strlen(str) - 1;
	while (len >= 0)
		if (str[len--] == quote)
			count++;
	return count;
}

char* quote_closer(char quote)
{
	char *closer;
	int count;

	count = 0;
	closer = readline("quote > ");
	count = quote_counter(closer,quote);
	if ((count % 2) != 1)
	{
		char* recursive_result = quote_closer(quote);
		size_t total_len = strlen(closer) + strlen(recursive_result) + 1;
		char* result = malloc(total_len);
		strcpy(result, closer);
		strcat(result, recursive_result);
		free(closer);
		free(recursive_result);
		return result;
	}
	return closer;
}

char *quote_master(char quote)
{
	char * qc = quote_closer(quote);
	if (quote == '"')
	{
		qc = ft_replace(qc,"\"\"","\\n");
		qc = ft_replace(qc,"\"","\\n");
	}
	else if (quote == '\'')
	{
		printf("%s\n", qc);
		qc = ft_replace(qc,"\'\'","\\n");
		qc = ft_replace(qc,"\'","\\n");
	}
	return qc;
}
