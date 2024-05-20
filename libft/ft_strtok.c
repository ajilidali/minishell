/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:34:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/20 17:04:27 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtok(char *str, const char *delim) {
    static char *next_token = NULL;  // Holds the position of the next token
    char *token_start = NULL;        // Holds the start position of the current token

    // If str is not NULL, update next_token to point to str
    if (str != NULL) {
        next_token = str;
    }

    // If next_token is NULL or empty string, return NULL (no more tokens)
    if (next_token == NULL || *next_token == '\0') {
        return NULL;
    }

    // Find the start of the token
    token_start = next_token;
    
    // Find the end of the token
    while (*next_token != '\0' && ft_strchr(delim, *next_token) != NULL) {
        next_token++;
    }

    // If the end of the string is reached, set next_token to NULL
    if (*next_token == '\0') {
        next_token = NULL;
    } else {
        // Replace the delimiter with null character to terminate the token
        *next_token = '\0';
        // Move next_token to the next character after the delimiter
        next_token++;
    }

    // Return the start position of the token
    return token_start;
}
