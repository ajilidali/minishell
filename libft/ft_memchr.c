/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:46:44 by moajili           #+#    #+#             */
/*   Updated: 2024/01/29 10:35:47 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned int	i;

	if (memoryBlock == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (*(char *)memoryBlock == (char)searchedChar)
			return ((void *)memoryBlock);
		memoryBlock++;
		i++;
	}
	return (NULL);
}
