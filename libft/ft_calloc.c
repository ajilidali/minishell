/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:55:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:23:43 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Allocates memory for an array of 'count' elements,
 each of them size bytes long, and initializes all its bits to zero.
 * @param count Number of elements to allocate.
 * @param size Size of each element.
 * @return A pointer to the allocated memory,
 * which is suitably aligned for any built-in type.
 * If the function fails to allocate the memory, it returns NULL.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = ft_malloc(count * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}
