/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:47:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/07 10:32:22 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (EXIT_SUCCESS);
}
