/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:27:02 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Locates the first occurrence of 'c'
 * (converted to a char) in the string pointed to by 's'.
 * The terminating null character is considered
 * to be part of the string; therefore if 'c' is '\0',
 * the functions locate the terminating '\0'.
 * @param s The string to be scanned.
 * @param c The character to be searched.
 * @return A pointer to the first occurrence of
 * the character 'c' in the string 's', or NULL
 * if the character is not found.
 */
char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	chr;

	i = 0;
	chr = (unsigned char)c;
	while (s[i] != '\0' && s[i] != chr)
		s++;
	if (s[i] == chr)
		return ((char *)&s[i]);
	return (NULL);
}
