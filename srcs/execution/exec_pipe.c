/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:45:44 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/29 13:41:13 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_command(ASTNode *node, MS *ms)
{
	char	*path;
	char	**envp;

	envp = get_tabenv(ms->env);
	if (!envp)
		exit(1);
	if (!node->args[0])
		exit(0);
	if (!access(node->args[0], X_OK))
		path = ft_strdup(node->args[0]);
	else
		path = find_path(node->args[0], envp);
	if (!path)
	{
		check_path(node->args[0]);
		print_errors(node->args[0], ER_CMD_NOT_FOUND);
		freetab(envp);
		exit(127);
	}
	if (execve(path, node->args, envp) == -1)
	{
		free(path);
		freetab(envp);
	}
	exit(1);
}

// Pipe --> Right
int	ft_fork_right(ASTNode *node, MS *mini, int pipefd[2])
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		setup_redirections(node);
		if (node->fd_in != STDIN_FILENO)
		{
			if (dup2(node->fd_in, STDIN_FILENO) == -1)
				exit(1);
		}
		else
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
				exit(1);
		if (node->fd_out != STDOUT_FILENO)
			if (dup2(node->fd_out, STDOUT_FILENO) == -1)
				exit(1);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_pipe(node, mini);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

// Pipe --> Left
int	ft_fork_left(ASTNode *node, MS *mini, int pipefd[2])
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		setup_redirections(node);
		if (node->fd_in != STDIN_FILENO)
			if (dup2(node->fd_in, STDIN_FILENO) == -1)
				exit(1);
		if (node->fd_out != STDOUT_FILENO)
		{
			if (dup2(node->fd_out, STDOUT_FILENO) == -1)
				exit(1);
		}
		else
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit(1);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_pipe(node, mini);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	make_pipe(ASTNode *node, MS *ms)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	ms->exit_code = ft_fork_left(node->left, ms, pipefd);
	close(pipefd[1]);
	ms->exit_code = ft_fork_right(node->right, ms, pipefd);
	close(pipefd[0]);
}

void	exec_pipe(ASTNode *node, MS *mini)
{
	int	exit;

	exit = 0;
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
	{
		if (get_argc(node->args) < 1)
			node->args = filter_argv(node->args, "");
		exit = is_local_fct(mini, node);
		if (exit != -1)
			mini->exit_code = exit;
		exec_command(node, mini);
	}
	else if (node->type == AST_PIPELINE)
		make_pipe(node, mini);
}
