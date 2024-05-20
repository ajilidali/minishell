/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:46:40 by moajili           #+#    #+#             */
/*   Updated: 2023/11/23 13:03:47 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;

	if (dest == NULL && src == NULL)
		return (dest);
	destination = (char *)dest;
	source = (const char *)src;
	while (n--)
		*destination++ = *source++;
	return (dest);
}
