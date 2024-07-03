/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:45:44 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/03 16:02:28 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(ASTNode *node, MS *ms)
{
	char	*path;
	char	**envp;

	check_path(node->args[0]);
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

// Pipe --> Right
void	ft_fork_right(ASTNode *node, MS *mini, int pipefd[2])
{
	int	pid;

	pid = fork();
	node->fd_out = 1;
	node->fd_in = 0;
	if (pid == -1)
		return ;
	if (pid == 0)
	{
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
		exit(0);
	}
}

// Pipe --> Left
void	ft_fork_left(ASTNode *node, MS *mini, int pipefd[2])
{
	int	pid;

	pid = fork();
	node->fd_out = 1;
	node->fd_in = 0;
	if (pid == -1)
		return ;
	if (pid == 0)
	{
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
		exit(0);
	}
}

void make_pipe(ASTNode *node, MS *ms)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	ft_fork_left(node->left, ms, pipefd);
	ft_fork_right(node->right, ms, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
}

void	exec_pipe(ASTNode *node, MS *mini)
{
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
	{
		node->args = filter_argv(get_argc(node->args), node->args, "");
		if (is_local_fct(mini, node) != -1)
			return ;
		exec_command(node, mini);
	}
	else if (node->type == AST_PIPELINE)
		make_pipe(node, mini);
}
