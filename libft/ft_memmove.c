/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:02:22 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies 'len' bytes from memory area 'src' to memory area 'dst'.
 * The memory areas may overlap:
 * copying takes place as though the bytes in 'src'
 * are first copied into a temporary array
 * that does not overlap 'src' or 'dst',
 * and the bytes are then copied from the temporary array to 'dst'.
 * @param dst The memory area to copy to.
 * @param src The memory area to copy from.
 * @param len The number of bytes to copy.
 * @return A pointer to 'dst'.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	else if (dst >= src)
	{
		while (len != 0)
		{
			*(char *)(dst + (len - 1)) = *(char *)(src + (len - 1));
			len--;
		}
	}
	return (dst);
}
