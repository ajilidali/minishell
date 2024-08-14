/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:50:46 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 20:10:20 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		j;
	char	*anchor;

	if (!(*to_find))
		return (str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			anchor = ((char *)str + i);
			while (str[i] && to_find[j] && str[i] == to_find[j])
			{
				if (to_find[j + 1] == '\0')
					return (anchor);
				i++;
				j++;
			}
			if (!str[i])
				return (0);
		}
	}
	return (0);
}
