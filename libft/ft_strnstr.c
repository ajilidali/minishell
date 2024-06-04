/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:53:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Locates the first occurrence of
 * the null-terminated string 'little' in the string 'big',
 * where not more than 'len' characters are searched.
 * Characters that appear after a `\0' character are not searched.
 * If 'little' is an empty string, 'big' is returned;
 * if 'little' occurs nowhere in 'big',
 * NULL is returned;
 * otherwise a pointer to the first character
 * of the first occurrence of 'little' is returned.
 * @param big The string to be scanned.
 * @param little The string to be searched within 'big'.
 * @param len The maximum number of characters to be searched in 'big'.
 * @return A pointer to the first occurrence of 'little' in 'big',
 * or NULL if 'little' is not found in the first 'len' characters of 'big'.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if ((!big || !little) && len == 0)
		return (NULL);
	if (!little_len)
		return ((char *)big);
	while (big[i] && len >= i + little_len)
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(big + i, little, little_len) == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
