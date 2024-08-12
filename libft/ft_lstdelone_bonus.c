/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:14:01 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 00:34:31 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Takes as a parameter an element and frees the
 * memory of the element’s content
 * using the function 'del' given as a parameter,
 * then frees the element itself.
 * The memory of 'next' is not freed.
 * @param lst The element to free.
 * @param del The address of the function used to delete the content.
 * If 'lst' or 'del' is NULL, the function does nothing.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && (*del))
	{
		del(lst->content);
		ft_free(lst);
	}
}
