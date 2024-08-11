/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/11 13:46:47 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_list(t_list *env)
{
	t_list	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->content);
		free(tmp);
	}
}

t_list	*lnew_node(char *name_value)
{
	t_list	*node;
	char	*folder;

	if (!name_value)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	folder = ft_strjoin("/", name_value);
	node->content = folder;
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

int	add_node(char *content, t_list *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	list->next = lnew_node(content);
	if (!list->next)
		return (0);
	return (1);
}

void	delete_last_node(t_list *list)
{
	t_list	*temp;

	if (!list)
		return ;
	temp = list;
	while (temp->next)
	{
		list = temp;
		temp = temp->next;
	}
	list->next = NULL;
	free(temp->content);
	free(temp);
}
