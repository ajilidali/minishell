/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:44:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/04/19 23:06:22 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Checks if the passed character is a digit.
 * @param a The character to check.
 * @return Returns 1 if the character is a digit (0-9), 0 otherwise.
 */
int	ft_isdigit(int a)
{
	return ((a >= 48 && a <= 57));
}
