/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:14:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/04/19 23:36:02 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Converts the lowercase letter 'c' to 
 * its uppercase equivalent if 'c' is a lowercase 
 * letter and has a uppercase equivalent. 
 * If the argument is not a lowercase letter, 
 * the argument is returned unchanged.
 * @param c The character to be converted.
 * @return The uppercase equivalent to 'c', 
 * if such value exists, or 'c' (unchanged) otherwise. 
 * The value is returned as an int value 
 * that can be implicitly casted to char.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
