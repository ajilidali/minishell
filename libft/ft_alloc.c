/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:35:38 by sakaido           #+#    #+#             */
/*   Updated: 2024/08/12 18:59:53 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*allocate_string(size_t length)
{
	char	*str;

	str = ft_calloc(length + 1, 1);
	if (!str)
	{
		ft_putstr_fd("malloc", STDERR_FILENO);
		return (NULL);
	}
	return (str);
}
