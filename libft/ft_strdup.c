/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:07:42 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 12:05:48 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns a pointer to a new string which is a duplicate of the string 's'.
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3).
 * @param s The string to duplicate.
 * @return A pointer to the duplicated string.
 * It returns NULL if insufficient memory was available.
 */
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
