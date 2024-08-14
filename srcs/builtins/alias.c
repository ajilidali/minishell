/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:47:01 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 20:51:41 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	alias_finder(t_alias *aliases, char *cmd, int alias_count)
{
	int	i;

	i = 0;
	while (i < alias_count)
	{
		if (ft_strcmp(aliases[i].cmd, cmd) == 0)
			return (i);
		i++;
	}
	return (-1);
}


void	trim_whitespace(char *str)
{
	char	*end;

	while (*str == ' ')
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;
	*(end + 1) = '\0';
}

// Attention fonction pas protege si erreur de malloc
void	assign_alias(t_ms *mini, char *alias, char *cmd)
{
	int	replace;

	replace = alias_finder(mini->aliases, alias, mini->alias_count);
	if (replace != -1)
	{
		mini->aliases[replace].cmd = ft_strdup(alias);
		mini->aliases[replace].value = ft_strdup(cmd);
		return ;
	}
	mini->aliases[mini->alias_count].cmd = ft_strdup(alias);
	mini->aliases[mini->alias_count].value = ft_strdup(cmd);
	mini->alias_count++;
}

void	process_arguments(t_ms *mini, int argc)
{
	int		i;
	char	*arg;
	char	*equal_sign;
	char	*left_part;
	char	*right_part;

	i = 1;
	while (i < argc)
	{
		arg = mini->ast->args[i];
		equal_sign = ft_strchr(arg, '=');
		if (equal_sign)
		{
			left_part = ft_strndup(arg, equal_sign - arg);
			right_part = ft_strdup(equal_sign + 1);
			trim_whitespace(left_part);
			trim_whitespace(right_part);
			if (*right_part != '\0' && *left_part != '\0')
				assign_alias(mini, left_part, right_part);
			ft_free(left_part);
			ft_free(right_part);
		}
		i++;
	}
}

int	print_aliases(t_alias *aliases, int alias_count)
{
	int	i;

	i = 0;
	if (!aliases)
		return (1);
	while (i <= alias_count)
	{
		if (aliases[i].cmd)
			printf("alias %s='%s'\n", aliases[i].cmd, aliases[i].value);
		i++;
	}
	return (0);
}

int	run_alias(t_ms *mini, t_astnode *node)
{
	int	argc;

	argc = 0;
	if (!node)
		return (1);
	while (node->args[argc])
		argc++;
	if (argc == 1)
		return (print_aliases(mini->aliases, mini->alias_count));
	process_arguments(mini, argc);
	return (0);
}
