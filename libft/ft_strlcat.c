/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:42:01 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies up to 'dstsize' - 1 characters
 * from the string 'src' to 'dst',
 * NUL-terminating the result if 'dstsize' is not 0.
 * If the 'src' and 'dst' strings overlap, the behavior is undefined.
 * @param dst The destination string.
 * @param src The source string.
 * @param dstsize The size of the destination string.
 * @return The total length of the string they tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;
	size_t	len;
	size_t	lenght;

	lenght = ft_strlen(src);
	if (ft_memchr(dst, '\0', dstsize) == NULL)
		return (lenght + dstsize);
	i = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= i)
		return (lenght + dstsize);
	len = i + lenght;
	y = 0;
	while (i < (dstsize - 1) && src[y])
		dst[i++] = src[y++];
	dst[i] = '\0';
	return (len);
}
