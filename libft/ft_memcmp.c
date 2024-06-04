/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:43:19 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Compares the first 'n' bytes
 * (each interpreted as unsigned char) of
 * the memory areas 's1' and 's2'.
 * @param s1 The first memory area.
 * @param s2 The second memory area.
 * @param n The number of bytes to compare.
 * @return An integer less than, equal to,
 * or greater than zero if 's1' is found, respectively,
 * to be less than, to match, or be greater than 's2'.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*target1;
	const char	*target2;

	i = 0;
	target1 = s1;
	target2 = s2;
	if (n == 0)
		return (0);
	while (i + 1 < n && target1[i] == target2[i])
		i++;
	return ((unsigned char)target1[i] - (unsigned char)target2[i]);
}
