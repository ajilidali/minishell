/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:14:09 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 22:34:10 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_pidl	*ft_pidnew(int pid)
{
	t_pidl	*tab;

	tab = (t_pidl *)ft_malloc(sizeof(t_pidl));
	if (!tab)
		return (NULL);
	tab->pid = pid;
	tab->next = NULL;
	return (tab);
}

int	add_node_to_list(t_pidl **head, int pid)
{
	t_pidl	*new_node;
	t_pidl	*tmp;

	new_node = (t_pidl *)ft_malloc(sizeof(t_pidl));
	if (!new_node)
		return (1);
	new_node->pid = pid;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (0);
}

void	free_pidl(t_pidl **list_pid)
{
	t_pidl	*tmp;

	tmp = NULL;
	while (*list_pid)
	{
		tmp = (*list_pid)->next;
		ft_free(*list_pid);
		*list_pid = tmp;
	}
	*list_pid = NULL;
}

int	wait_pids(int pid, int flag)
{
	static t_pidl	*list_pid = NULL;
	t_pidl			*current;
	int				status;

	current = NULL;
	if (flag)
	{
		if (add_node_to_list(&list_pid, pid))
			return (free_pidl(&list_pid), 1);
		return (0);
	}
	else
	{
		current = list_pid;
		while (current)
		{
			waitpid((int)current->pid, &status, 0);
			if (!WTERMSIG(status))
				give_mini(NULL, 0)->exit_code = WEXITSTATUS(status);
			current = current->next;
		}
		return (free_pidl(&list_pid), 0);
	}
}
