/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:56:20 by moajili           #+#    #+#             */
/*   Updated: 2023/11/03 16:58:46 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*buffer;
	t_list	*debut;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	debut = NULL;
	while (lst)
	{
		content = f(lst->content);
		buffer = ft_lstnew(content);
		if (!buffer)
		{
			del(content);
			free(buffer);
			ft_lstclear(&debut, del);
			return (NULL);
		}
		ft_lstadd_back(&debut, buffer);
		lst = lst->next;
	}
	return (debut);
}
