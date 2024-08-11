/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:14:09 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/10 05:38:18 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_pidl	*ft_pidnew(int pid)
{
	t_pidl	*tab;

	tab = ft_calloc(1, sizeof(t_pidl));
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

	new_node = ft_pidnew(pid);
	if (!new_node)
		return (1);
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (0);
}

void	free_pidl(t_pidl *list_pid)
{
	t_pidl	*tmp;

	while (list_pid)
	{
		tmp = list_pid->next;
		free(list_pid);
		list_pid = tmp;
	}
}

int	wait_pids(int pid, int flag)
{
	static t_pidl	*list_pid = NULL;
	int				status;

	if (flag)
	{
		if (add_node_to_list(&list_pid, pid))
		{
			free_pidl(list_pid);
			return (1);
		}
		return (0);
	}
	else
	{
		while (list_pid)
		{
			waitpid((int)list_pid->pid, &status, 0);
			give_mini(NULL, 0)->exit_code = WEXITSTATUS(status);
			list_pid = list_pid->next;
		}
		return (0);
	}
}
