/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:01:17 by moajili           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Appends the string pointed to by 's2'
 * to the end of the string pointed to by 's1'.
 * The terminating null character in 's1'
 * is overwritten by the first character of 's2',
 * and a null-character is included
 *  at the end of the new string formed
 * by the concatenation of both in 's1'.
 * @param s1 The string to be appended on.
 * @param s2 The string to append to 's1'.
 * @return A pointer to the resulting string 's1'.
 */
char	*ft_strcat(char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	y;

	i = ft_strlen(s1);
	y = 0;
	while (s2[y])
	{
		s1[i + y] = s2[y];
		y++;
	}
	s1[i + y] = '\0';
	return (s1);
}
