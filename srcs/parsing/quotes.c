/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/08/11 17:33:17 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	char_counter(const char *str, char c)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(str) - 1;
	while (len >= 0)
		if (str[len--] == c)
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
	count = char_counter(closer, quote);
	if ((count % 2) != 1)
	{
		recursive_result = quote_closer(quote);
		total_len = ft_strlen(closer) + ft_strlen(recursive_result) + 1;
		result = allocate_string(total_len);
		ft_strcpy(result, closer);
		ft_strcat(result, recursive_result);
		ft_free(closer);
		ft_free(recursive_result);
		return (result);
	}
	return (closer);
}

char	*quote_master(char quote)
{
	char	*qc;

	qc = quote_closer(quote);
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
