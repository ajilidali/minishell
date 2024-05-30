/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:28 by moajili           #+#    #+#             */
/*   Updated: 2024/05/30 20:18:17 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char* quote_closer(char quote)
{
    char *closer;
    int len;
    int count;
    count = 0;

    closer = readline("quote > ");
    len = ft_strlen(closer) - 1;
    while (len >= 0)
        if (closer[len--] == quote)
            count++;

    if ((count % 2) != 1)
    {
        char* recursive_result = quote_closer(quote);
        size_t total_len = ft_strlen(closer) + ft_strlen(recursive_result) + 1;
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
        qc = ft_replace(qc,"\'\'","\\n");
        qc = ft_replace(qc,"\'","\\n");
    }
    return qc;
}
