/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:59:58 by hclaude           #+#    #+#             */
/*   Updated: 2024/04/19 23:05:54 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Checks if the passed character is alphabetic.
 * @param a The character to check.
 * @return Returns 1 if the character is an alpha, 0 otherwise.
 */
int	ft_isalpha(int a)
{
	return ((a >= 65 && a <= 90) || (a >= 97 && a <= 122));
}
