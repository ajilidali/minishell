/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:47:08 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Scans the initial 'n' bytes of the memory
 * area pointed to by 's' for the first instance of 'c'.
 * Both 'c' and the bytes of the memory area
 * pointed to by 's' are interpreted as unsigned char.
 * @param s The memory area.
 * @param c The byte to search for.
 * @param n The number of bytes to scan.
 * @return A pointer to the matching byte or NULL
 * if the character does not occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(char *)s == (char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
