/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:23:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/07 10:32:22 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_gb(t_gc *gc, void *str)
{
	t_gc	*new;
	t_gc	*tmp;

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

void	*ft_free_gc(t_gc *gc)
{
	t_gc	*tmp;

	while (gc)
	{
		tmp = gc;
		gc = gc->next;
		free(tmp->str);
		free(tmp);
	}
	gc = NULL;
	return (NULL);
}

void	*ft_malloc(size_t size, int flag_free)
{
	static t_gc	*gc = NULL;
	void		*result;

	if (flag_free)
		return (ft_free_gc(gc));
	if (!gc)
	{
		gc = ft_init_gc();
		if (!gc)
			return (NULL);
	}
	result = malloc(size);
	if (!result)
		return (NULL);
	if (!ft_add_gb(gc, result))
		return (free(result), NULL);
	return (result);
}
