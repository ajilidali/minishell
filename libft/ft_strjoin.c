/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:00:54 by moajili           #+#    #+#             */
/*   Updated: 2024/04/17 12:34:42 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (ret == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memset(ret, 0, (len1 + len2 + 1) * sizeof(char));
	ft_memcpy(ret, s1, len1);
	ft_memcpy(ret + len1, s2, len2 + 1);
	return (ret);
}

char	*ft_ustrjoin(char *s1, char *s2)
{
	size_t len1;
	size_t len2;
	char *ret;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, 0, (len1 + len2 + 1) * sizeof(char));
	ft_memcpy(ret, s1, len1);
	ft_memcpy(ret + len1, s2, len2 + 1);
	free(s1);
	return (ret);
}