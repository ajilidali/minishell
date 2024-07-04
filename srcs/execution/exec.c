/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:54:48 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/04 16:10:17 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

int	make_redirection(ASTNode *node)
{
	setup_redirections(node);
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

	check_path(node->args[0]);
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
		ft_putstr_fd("DEDSEC: ", STDERR_FILENO);
		ft_putstr_fd(node->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
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

void print_redirections(ASTNode *node)
{
	size_t i;

	i = 0;
	while (i < node->redirections_count)
	{
		printf("redirections[%zu]: %d %s\n", i, node->redirections[i].flag, node->redirections[i].file);
		i++;
	}
}

int	exec_commands(ASTNode *node, MS *ms)
{
	int	pid;
	int	status;

	print_redirections(node);
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
		printf("status: %d\n", WEXITSTATUS(status));
		return (1);
	}
	else
		exec_pipe(node, ms);
	return (666);
}
