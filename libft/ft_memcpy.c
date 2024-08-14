/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:28:12 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies 'n' bytes from memory area 'src' to memory area 'dst'.
 * If 'src' and 'dst' overlap, behavior is undefined.
 * Applications in which 'src' and 'dst'
 * might overlap should use memmove(3) instead.
 * @param dst The memory area to copy to.
 * @param src The memory area to copy from.
 * @param n The number of bytes to copy.
 * @return A pointer to 'dst'.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	size_t	i;

	dest = dst;
	i = 0;
	if (src == NULL && dst == NULL)
		return (dest);
	while (i < n)
	{
		dest[i] = *(char *)src;
		src++;
		i++;
	}
	return (dest);
}
