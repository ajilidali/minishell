/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:34:07 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Sets the first 'n' bytes of the block of memory pointed by 's' to zero.
 * @param s Pointer to the block of memory to fill.
 * @param n Number of bytes to be set to zero.
 */
void	ft_bzero(void *s, size_t n)
{
	char	*target;

	target = s;
	while (n--)
		*target++ = '\0';
}
