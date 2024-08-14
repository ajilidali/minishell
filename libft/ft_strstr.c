/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:50:46 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 17:08:06 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[++i])
		if (str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j])
				if (to_find[j++] == '\0')
					return ((char *)&str[i]);
			j = 0;
		}
	return (0);
}
