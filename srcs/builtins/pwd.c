/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:47:06 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 17:53:46 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_pwd(void)
{
	char	*path;

	path = env_get_var("PWD", give_envp(NULL, 0));
	if (!path)
		path = getcwd(NULL, 0);
	if (!path)
		return (perror("DEDSEC "), EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	ft_free(path);
	return (EXIT_SUCCESS);
}
