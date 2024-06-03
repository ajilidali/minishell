/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:32:58 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Deletes and frees the given element and
 * every successor of that element, using the function 'del' and free(3).
 * Finally, the pointer to the list is set to NULL.
 * @param lst The address of a pointer to an element.
 * @param del The address of the function used to
 * delete the content of the element.
 * If 'lst' or 'del' is NULL, the function does nothing.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst && (*del))
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, (*del));
			*lst = temp;
		}
	}
	lst = NULL;
}
