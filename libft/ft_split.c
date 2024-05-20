/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:37:21 by moajili           #+#    #+#             */
/*   Updated: 2024/05/13 13:25:56 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	jecompte(char const *s, char c)
{
	int	compte;
	int	i;

	compte = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			compte++;
		while (s[i] != c && s[i])
			i++;
	}
	return (compte);
}

static char	*init_str(char const *s, char c)
{
	int		i;
	char	*point;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	point = (char *)malloc(sizeof(char) * (i + 1));
	if (!point)
		return (NULL);
	ft_memcpy(point, s, i);
	point[i] = '\0';
	return (point);
}

static void	freetab(char **point)
{
	int	i;

	i = 0;
	while (point[i])
	{
		free(point[i]);
		i++;
	}
	free(point);
}

char	**ft_split(char const *s, char c)
{
	char	**point;
	int		i;
	int		j;

	point = (char **)malloc(sizeof(char *) * (jecompte(s, c) + 1));
	if (!s || !point)
		return (NULL);
	i = 0;
	j = 0;
	while (i < jecompte(s, c))
	{
		while (s[j] == c)
			j++;
		point[i] = init_str(s + j, c);
		if (!point[i])
		{
			freetab(point);
			return (NULL);
		}
		j += ft_strlen(point[i]);
		i++;
	}
	point[i] = NULL;
	return (point);
}
