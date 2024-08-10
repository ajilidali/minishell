/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 04:39:11 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/10 05:43:39 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(list_commands *list)
{
	list_commands	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

list_commands	*create_list_node(ASTNode *node)
{
	list_commands	*new_node;

	new_node = (list_commands *)malloc(sizeof(list_commands));
	if (!new_node)
		return (NULL);
	new_node->args = node->args;
	new_node->fd_in = node->fd_in;
	new_node->fd_out = node->fd_out;
	new_node->redirections = node->redirections;
	new_node->redirections_count = node->redirections_count;
	new_node->redirections_capacity = node->redirections_capacity;
	new_node->save_in = node->save_in;
	new_node->save_out = node->save_out;
	new_node->next = NULL;
	return (new_node);
}

int	copy_ast_in_list(ASTNode *node, list_commands **head)
{
	list_commands	*new_node;
	list_commands	*temp;

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
