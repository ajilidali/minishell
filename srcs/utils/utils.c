/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:14:13 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/05 21:25:32 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freetab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

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

t_env *give_envp(char **envp, int i)
{
    static t_env *env = NULL;

    if (i == COPY && envp)
	{ 
        if (env)
            free_env(env);
        env = copy_env(envp);
    }
    return env;
}

void update_envp(MS *mini)
{
	mini->envp = give_envp(NULL, 0);
}

void test_envp(t_env *env, char *str)
{
   // t_env *env = give_envp(envp, COPY); // COPY is 10

    if (env)
	{
        printf("Before: %s\n", env->name_value);
        free(env->name_value);
        env->name_value = strdup(str);
        printf("After: %s\n", env->name_value);
    }
}
