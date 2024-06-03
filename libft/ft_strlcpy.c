/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:47:30 by hclaude           #+#    #+#             */
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
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[i] && i < dstsize - 1 && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	while (src[len])
		len++;
	return (len);
}
