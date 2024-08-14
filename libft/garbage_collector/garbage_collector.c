/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:23:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 16:15:26 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int	ft_add_gb(t_gc *gc, void *str)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
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

int	ft_free_node(t_gc **gc, void *ptr)
{
	t_gc	*prev;
	t_gc	*current;

	if (!gc || *gc)
		return (0);
	prev = NULL;
	current = *gc;
	while (current)
	{
		if (current->str == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*gc = current->next;
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
				return (free(result), 0);
		}
		if (!ft_add_gb(gc, result))
			return (free(result), 0);
		return (1);
	}
	if (flag == FREE_PTR)
		return (ft_free_node(&gc, result));
	if (flag == FREE_GB)
		return (ft_free_gc(&gc), 1);
	return (1);
}
