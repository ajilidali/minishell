/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:58:08 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 17:26:32 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Iterates the list 'lst' and applies
 * the function 'f' to the content of each element.
 * Creates a new list resulting of
 * the successive applications of the function 'f'.
 * The 'del' function is used to delete
 * the content of an element if needed.
 * @param lst The address of a pointer to an element.
 * @param f The address of the function
 * used to iterate on the list.
 * @param del The address of the function used
 * to delete the content of the element.
 * @return The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;
	void	*temp;

	new_lst = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		temp = f(lst->content);
		new_elem = ft_lstnew(temp);
		if (!new_elem)
		{
			del(temp);
			ft_free(new_elem);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	return (new_lst);
}
