/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:35:38 by sakaido           #+#    #+#             */
/*   Updated: 2024/08/11 17:55:15 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *allocate_string(size_t length)
{
	char *str;

	str = ft_calloc(length + 1,1);
	if (!str)
	{
		ft_putstr_fd("malloc", STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
	str[length] = '\0';
	return (str);
}
