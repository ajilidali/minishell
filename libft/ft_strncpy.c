/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:54:57 by moajili           #+#    #+#             */
/*   Updated: 2024/05/24 16:57:20 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy( char *dest, const char *src, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (count < n && src[count])
	{
		dest[count] = src[count];
		count++;
	}
	while (count < n)
		dest[count++] = 0;
	return (dest);
}