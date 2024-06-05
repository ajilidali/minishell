/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:00:20 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/05 16:10:44 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_export(char *command)
{
	int	i;

	i = 0;
	while (command[i] && command[i] != '=')
		i++;
	if (command[i++] == '=' && command[i] != '=')
		return (1);
	return (0);
}

static t_env	*find_variable(char *variable, t_env *env)
{
	int	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(variable, env->name_value, i) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*split_list(t_env *head)
{
	t_env	*slow;
	t_env	*fast;
	t_env	*prev;

	if (!head || !head->next)
		return (head);
	slow = head;
	fast = head;
	prev = NULL;
	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	prev->next = NULL;
	return (slow);
}

t_env	*merge_sorted_lists(t_env *a, t_env *b)
{
	t_env	*result;

	if (!a)
		return (b);
	if (!b)
		return (a);
	result = NULL;
	if (strcmp(a->name_value, b->name_value) <= 0)
	{
		result = a;
		result->next = merge_sorted_lists(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge_sorted_lists(a, b->next);
	}
	return (result);
}

t_env	*merge_sort(t_env *head)
{
	t_env	*middle;
	t_env	*left;
	t_env	*right;

	if (!head || !head->next)
		return (head);
	middle = split_list(head);
	left = merge_sort(head);
	right = merge_sort(middle);
	return (merge_sorted_lists(left, right));
}

void free_env_list(t_env *head)
{
    t_env *tmp;

    while (head != NULL)
	{
        tmp = head;
        head = head->next;
        free(tmp->name_value);
        free(tmp);
    }
}

int	print_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (EXIT_SUCCESS);
	tmp = merge_sort(env);
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(tmp->name_value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	//free_env_list(env);
	return (EXIT_SUCCESS);
}

int	run_export(char **command, t_env **env)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *env;
	if (!command[1])
		return (print_env(*env));
	if (!verify_export(command[1]))
		return (EXIT_SUCCESS);
	while (tmp->next)
		tmp = tmp->next;
	node = find_variable(command[1], *env);
	if (!node)
	{
		tmp->next = new_node(command[1]);
		if (!tmp->next)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	free(node->name_value);
	node->name_value = ft_strdup(command[1]);
	if (!node->name_value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
