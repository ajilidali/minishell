/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:51:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ispace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/*
 * Converts a string to a long integer.
 * @param nptr The string to convert.
 * @return The long integer representation of the string.
 * If the string starts with '-', the result is negative.
 * If the string starts with '+', the result is positive.
 * If the string starts with neither, the result is positive.
 * If the string contains non-digit characters, they are ignored.
 */
long	ft_atol(const char *nptr)
{
	long	i;
	long	result;
	int		negative;

	result = 0;
	negative = 1;
	i = 0;
	while (ispace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negative = -1;
		i++;
	}
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
	{
		if (ft_isdigit(nptr[i]))
			result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * negative);
}
