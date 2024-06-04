/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:29:01 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Applies the function 'f' to each
 * character of the string 's', and passing its index as first argument.
 * Each character is passed by address to 'f' to be modified if necessary.
 * @param s The string on which to iterate.
 * @param f The function to apply to each character of 's' and its index.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!f)
		return ;
	if (s)
	{
		while (s[i])
		{
			f(i, s + i);
			i++;
		}
	}
}
