/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:27:21 by hclaude           #+#    #+#             */
/*   Updated: 2024/04/19 23:06:09 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Checks if the passed character is an ASCII character.
 * @param a The character to check.
 * @return Returns 1 if the character is an ASCII character (0-127), 0 otherwise.
 */
int	ft_isascii(int a)
{
	return ((a >= 0 && a <= 127));
}
