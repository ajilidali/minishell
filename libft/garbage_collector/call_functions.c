/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:43:54 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/13 14:19:54 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_exit(int status)
{
	int	fd;

	fd = 3;
	ft_free_gb();
	while (fd < 1000)
		close(fd++);
	exit(status);
}

void	ft_free_gb(void)
{
	ft_garbage(FREE_GB, NULL);
}

void	ft_free(void *ptr)
{
	ft_garbage(FREE_PTR, ptr);
}

void	*ft_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		return (NULL);
	else
	{
		if (!ft_garbage(3, result))
			return (NULL);
		return (result);
	}
}
