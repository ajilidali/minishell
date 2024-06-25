/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/06/07 10:32:22 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_counter(const char *str, char quote)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(str) - 1;
	while (len >= 0)
		if (str[len--] == quote)
			count++;
	return (count);
}

char	*quote_closer(char quote)
{
	size_t	total_len;
	char	*closer;
	char	*recursive_result;
	char	*result;
	int		count;

	count = 0;
	closer = readline("quote > ");
	count = quote_counter(closer, quote);
	if ((count % 2) != 1)
	{
		recursive_result = quote_closer(quote);
		total_len = ft_strlen(closer) + ft_strlen(recursive_result) + 1;
		result = malloc(total_len);
		ft_strcpy(result, closer);
		ft_strcat(result, recursive_result);
		free(closer);
		free(recursive_result);
		return (result);
	}
	return (closer);
}

char	*quote_master(char quote)
{
	char	*qc;

	qc = quote_closer(quote);
//	printf("%s",qc);
	if (quote == '"')
	{
		qc = ft_replace(qc, "\"\"", "\\n");
		qc = ft_replace(qc, "\"", "\\n");
	}
	else if (quote == '\'')
	{
		qc = ft_replace(qc, "\'\'", "\\n");
		qc = ft_replace(qc, "\'", "\\n");
	}
	return (qc);
}
