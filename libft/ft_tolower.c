/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:23:24 by hclaude           #+#    #+#             */
/*   Updated: 2024/04/19 23:29:23 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Converts the uppercase letter 'c' to its lowercase 
 * equivalent if 'c' is an uppercase letter and has a lowercase equivalent. 
 * If the argument is not an uppercase letter, 
 * the argument is returned unchanged.
 * @param c The character to be converted.
 * @return The lowercase equivalent to 'c', 
 * if such value exists, or 'c' (unchanged) otherwise. 
 * The value is returned as an int value that can be implicitly casted to char.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
