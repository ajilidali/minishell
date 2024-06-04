/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:10:34 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/04 16:17:24 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Marche pas bien car si plusieurs espaces entre mots, ces espaces ne sont pas affiches
// faut trouver une solution

int	echo_verif(char **command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[++i])
	{
		if (command[i][j++] == '-' && command[i][j] && command[i][j] == 'n')
		{
			while (command[i][j] == 'n')
			{
				j++;
			}
			if (command[i][j] != 'n' && command[i][j])
				return (i);
		}
		else
			return (i);
		j = 0;
	}
	return (i);
}

int	run_echo(char **command)
{
	int		option;
	int		n;

	n = 0;
	option = echo_verif(command);
	if (option > 1)
		n = 1;
	while (command[option])
	{
		ft_putstr_fd(command[option], STDOUT_FILENO);
		if (command[++option])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
