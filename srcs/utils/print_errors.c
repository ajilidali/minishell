/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:52:49 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 14:19:59 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_errors_first(char *str, int flag)
{
	if (flag == ER_SYNTAX_ERROR)
	{
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
	}
	else if (flag == ER_QUOTE_ERROR)
		ft_putendl_fd("DEDSEC: unexpected EOF", STDERR_FILENO);
	else if (flag == ER_REDIRECT_ERROR)
		ft_putendl_fd("DEDSEC: syntax error: expected file after redirection",
			STDERR_FILENO);
	else if (flag == ER_CMD_NOT_FOUND)
	{
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else if (flag == ER_PERM_DENIED)
	{
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
}

void	print_errors(char *str, int flag)
{
	print_errors_first(str, flag);
	if (flag == ER_NO_FILE_DIR)
	{
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (flag == ER_NO_FILE)
	{
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file\n", STDERR_FILENO);
	}
	else if (flag == ER_IS_DIR)
	{
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
}
