/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:21:43 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/25 17:47:17 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirection(ASTNode *node)
{
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	if (node->fd_in != STDIN_FILENO)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			close(node->fd_in);
			close(node->fd_out);
			return (0);
		}
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			close(node->fd_in);
			close(node->fd_out);
			return (0);
		}
	}
	return (1);
}

static int	exec_command(ASTNode *node, MS *ms)
{
	char	*path;
	char	**envp;

	if (!make_redirection(node))
		exit(1);
	envp = get_tabenv(ms->env);
	if (!envp)
		exit(1);
	if (!access(node->args[0], X_OK))
		path = ft_strdup(node->args[0]);
	else
		path = find_path(node->args[0], envp);
	if (!path)
	{
		freetab(envp);
		exit(1);
	}
	if (execve(path, node->args, envp) == -1)
	{
		free(path);
		freetab(envp);
		exit(1);
	}
	exit(1);
}

int	exec_commands(ASTNode *node, MS *ms)
{
	int	pid;
	int	status;

	if (node->type == AST_COMMAND)
	{
		status = is_local_fct(ms, node);
		if (status != -1)
			return (status);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			exec_command(node, ms);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status))
		{
			ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
			ft_putstr_fd(node->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			return (1);
		}
	}
	else
		exec_pipe(node, ms);
	return (666);
}
