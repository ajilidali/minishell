/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:47:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/04 09:17:40 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	ft_putstr_fd(path, STDOUT_FILENO);
	return (0);
}
