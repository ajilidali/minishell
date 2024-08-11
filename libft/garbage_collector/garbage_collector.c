/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:23:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:41:10 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int	ft_add_gb(t_gc *gc, void *str)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	printf("ADDRESS = %p\n", str);
	if (!new)
		return (0);
	new->str = str;
	new->next = NULL;
	while (gc->next)
		gc = gc->next;
	gc->next = new;
	return (1);
}

t_gc	*ft_init_gc(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->next = NULL;
	gc->str = NULL;
	return (gc);
}

void	ft_free_gc(t_gc **gc)
{
	t_gc	*tmp;

	while (*gc)
	{
		tmp = *gc;
		*gc = (*gc)->next;
		free(tmp->str);
		free(tmp);
	}
	gc = NULL;
	return ;
}

int	ft_free_node(t_gc *gc, void *ptr)
{
	t_gc	*prev;
	t_gc	*current;

	if (!gc)
		return (0);
	prev = NULL;
	current = gc;
	while (current)
	{
		if (current->str == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				gc = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	free(ptr);
	return (0);
}

int	ft_garbage(int flag, void *result)
{
	static t_gc	*gc = NULL;

	if (flag == 3)
	{
		if (!gc)
		{
			gc = ft_init_gc();
			if (!gc)
				return (0);
		}
		if (!ft_add_gb(gc, result))
			return (0);
		return (1);
	}
	if (flag == FREE_PTR)
		return (ft_free_node(gc, result));
	if (flag == FREE_GB)
		return (ft_free_gc(&gc), 1);
	return (1);
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
			return (free(result), NULL);
		return (result);
	}
}
