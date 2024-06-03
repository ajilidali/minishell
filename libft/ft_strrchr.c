/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:27:02 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Locates the last occurrence of 'c' (converted to a char)
 * in the string pointed to by 's'.
 * The terminating null character is considered to be part
 * of the string; therefore if 'c' is `\0', the functions
 * locate the terminating `\0'.
 * @param s The string to be scanned.
 * @param c The character to be searched within 's'.
 * @return A pointer to the located character,
 * or NULL if the character does not appear in the string.
 */
char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	chr;

	i = 0;
	chr = (unsigned char)c;
	while (s[i])
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == chr)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
