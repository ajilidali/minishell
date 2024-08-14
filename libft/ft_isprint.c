/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:48:01 by hclaude           #+#    #+#             */
/*   Updated: 2024/04/19 23:36:15 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
 * Checks if the passed character is printable.
 * @param c The character to check.
 * @return Returns 1 if the character 
 * is printable (ASCII value between 32 and 126 inclusive), 0 otherwise.
 */
int	ft_isprint(int c)
{
	return ((c >= 32 && c < 127));
}
