/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:35:38 by sakaido           #+#    #+#             */
/*   Updated: 2024/08/11 17:25:03 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_similar(const char *str1, const char *str2)
{
	return (ft_strcmp(str1, str2) == 0);
}

char	**filter_argv(char **argv, const char *target)
{
	int		i;
	int		j;
	int		count;
	char	**new_argv;

	i = 0;
	j = 0;
	count = 0;
	while (argv[i] != NULL)
		if (!is_similar(argv[i++], target))
			count++;
	new_argv = (char **)ft_malloc((count + 1) * sizeof(char *));
	if (new_argv == NULL)
		return (perror("Failed to allocate memory"), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (argv[i++] && !is_similar(argv[i], target))
	{
			new_argv[j] = argv[i];
			if (new_argv[j++] == NULL)
				return (perror("Failed to allocate memory"), exit(EXIT_FAILURE), NULL);
	}
	new_argv[j] = NULL;
	return (new_argv);
}

int	get_argc(char *argv[])
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}
