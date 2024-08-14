/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 04:39:11 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/13 20:17:50 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_cmd_list(t_lst_cmd *list)
{
	t_lst_cmd	*tmp;

	while (list)
	{
		tmp = list->next;
		ft_free(list);
		list = tmp;
	}
}

t_lst_cmd	*create_list_node(t_astnode *node)
{
	t_lst_cmd	*new_node;

	new_node = (t_lst_cmd *)ft_malloc(sizeof(t_lst_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = node->args;
	new_node->fd_in = node->fd_in;
	new_node->fd_out = node->fd_out;
	new_node->redirections = node->redirections;
	new_node->redirections_count = node->redirections_count;
	new_node->redirections_capacity = node->redirections_capacity;
	new_node->fd_in = STDIN_FILENO;
	new_node->fd_out = STDOUT_FILENO;
	new_node->next = NULL;
	return (new_node);
}

int	copy_ast_in_list(t_astnode *node, t_lst_cmd **head)
{
	t_lst_cmd	*new_node;
	t_lst_cmd	*temp;

	if (!node)
		return (1);
	if (node->type == AST_COMMAND)
	{
		new_node = create_list_node(node);
		if (!new_node)
			return (1);
		if (*head == NULL)
			*head = new_node;
		else
		{
			temp = *head;
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
		}
	}
	copy_ast_in_list(node->left, head);
	copy_ast_in_list(node->right, head);
	return (0);
}
