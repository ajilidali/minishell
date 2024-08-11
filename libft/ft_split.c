/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:49:25 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 16:51:28 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	countstr(char const *s, char c)
{
	int	i;
	int	nbstr;

	i = 0;
	nbstr = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			nbstr++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (nbstr);
}

static char	**sub(const char *s, char c, char **str, int len)
{
	size_t	i;
	size_t	sub_start;
	int		y;

	i = 0;
	sub_start = 0;
	y = 0;
	while (y < len)
	{
		while (s[i] == c && s[i])
			i++;
		sub_start = i;
		while (s[i] != c && s[i])
			i++;
		str[y++] = ft_substr(s, sub_start, i - sub_start);
		if (!str[y - 1])
			return (freetab(str), NULL);
	}
	return (str);
}

/*
 * Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting 's' using
 * the character 'c' as a delimiter.
 * The array must be ended by a NULL pointer.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings
 * resulting from the split. NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**str;
	int		len;

	if (!s)
		return (NULL);
	len = countstr(s, c);
	str = ft_calloc(len + 1, sizeof(char *));
	if (!str)
		return (NULL);
	if (!sub(s, c, str, len))
		return (NULL);
	return (str);
}
