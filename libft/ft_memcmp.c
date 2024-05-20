/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:46:42 by moajili           #+#    #+#             */
/*   Updated: 2023/11/03 14:33:09 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	while ((n - 1) > 0 && *(char *)s1 == *(char *)s2)
	{
		s1++;
		s2++;
		n--;
	}
	c1 = (unsigned char)*(char *)s1;
	c2 = (unsigned char)*(char *)s2;
	return (c1 - c2);
}
