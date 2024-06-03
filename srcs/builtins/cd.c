/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 14:53:46 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_cd(char **command)
{
	char	*home;

	if (!command[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (0);
		}
		if (chdir(home) == -1)
		{
			printf("cd: %s: %s\n", command[1], strerror(errno));
			return (0);
		}
	}
	else
	{
		if (chdir(command[1]) == -1)
		{
			printf("cd: %s: %s\n", command[1], strerror(errno));
			return (0);
		}
	}
	return (1);
}
