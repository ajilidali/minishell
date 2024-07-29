/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:47:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/29 14:37:47 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pwd(void)
{
	ft_putendl_fd("PWD", STDERR_FILENO);
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (EXIT_SUCCESS);
}
