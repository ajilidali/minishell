/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:14:13 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 20:53:26 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_tabenv(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tab = ft_calloc(sizeof(char *), (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = ft_strdup(env->name_value);
		if (!tab[i++])
			return (freetab(tab), NULL);
		env = env->next;
	}
	return (tab);
}

char	*copy_except_first_n_chars(const char *input, size_t n)
{
	char	*result;
	size_t	len;

	if (input == NULL)
	{
		result = (char *)ft_malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	len = ft_strlen(input);
	if (len <= n)
	{
		result = (char *)ft_malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	result = (char *)ft_malloc(len - n + 1);
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, input + n);
	return (result);
}

t_ms	*give_mini(t_ms *mini_cpy, int copy)
{
	static t_ms	*mini = NULL;

	if (copy)
	{
		mini = mini_cpy;
		return (mini);
	}
	return (mini);
}
