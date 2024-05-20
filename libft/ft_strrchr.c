/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:46:21 by moajili           #+#    #+#             */
/*   Updated: 2023/10/30 13:09:42 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char st[], int searchedChar)
{
	int	i;

	i = ft_strlen(st);
	while (i >= 0)
	{
		if (st[i] == (char)searchedChar)
			return ((char *)(st + i));
		i--;
	}
	return (NULL);
}
