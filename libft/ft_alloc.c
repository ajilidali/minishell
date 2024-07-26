/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:35:38 by sakaido           #+#    #+#             */
/*   Updated: 2024/07/26 22:13:40 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *allocate_string(size_t length)
{
    char *str;
	
	str = ft_calloc(length + 1,1);
    if (!str)
	{
        ft_putstr_fd("malloc",1);
        exit(EXIT_FAILURE);
    }
    str[length] = '\0';
    return (str);
}