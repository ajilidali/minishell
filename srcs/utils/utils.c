/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:14:13 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:39:00 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!env->hide)
			i++;
		env = env->next;
	}
	return (i);
}

char	**get_tabenv(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		i;

	tmp = env;
	i = get_env_size(env);
	tab = ft_calloc(sizeof(char *), (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (!tmp->hide)
		{
			tab[i] = ft_strdup(tmp->name_value);
			if (!tab[i++])
				return (freetab(tab), NULL);
		}
		tmp = tmp->next;
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
