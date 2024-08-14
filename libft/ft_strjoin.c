/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:17:49 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:38:19 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Allocates (with malloc(3)) and
 * returns a new string, which
 * is the result of the concatenation of 's1' and 's2'.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string. NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;
	int		y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[y++] = s1[i++];
	i = 0;
	while (s2[i])
		str[y++] = s2[i++];
	str[y] = '\0';
	return (str);
}
