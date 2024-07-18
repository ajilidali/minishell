/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:54:48 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/18 18:03:28 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_local_fct(MS *mini, ASTNode *node)
{
	int	exit_status;

	if (!node->args[0])
		return (0);
	exit_status = -1;
	if (ft_strcmp(node->args[0], "alias") == 0)
		exit_status = run_alias(mini, node);
	if (ft_strcmp(node->args[0], "cd") == 0)
		exit_status = run_cd(node->args, mini->env);
	if (ft_strcmp(node->args[0], "env") == 0)
		exit_status = run_env(mini->env);
	if (ft_strcmp(node->args[0], "export") == 0)
		exit_status = run_export(node->args, &mini->env);
	if (ft_strcmp(node->args[0], "echo") == 0)
		exit_status = run_echo(node->args);
	if (ft_strcmp(node->args[0], "pwd") == 0)
		exit_status = run_pwd();
	if (ft_strcmp(node->args[0], "unset") == 0)
		exit_status = run_unset(node->args, &mini->env);
	if (ft_strcmp(node->args[0], "exit") == 0)
		run_exit(node->args, mini);
	return (exit_status);
}

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

static void	exec_command(ASTNode *node, MS *ms)
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
	ft_putendl_fd(path, STDERR_FILENO);
	if (!path)
	{
		check_path(node->args[0]);
		print_errors(node->args[0], ER_CMD_NOT_FOUND);
		freetab(envp);
		exit(1);
	}
	if (execve(path, node->args, envp) == -1)
		return (print_errors(path, ER_PERM_DENIED), free(path),
			freetab(envp), exit(1));
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
		ms->exit_code = WEXITSTATUS(status); // recup
		return (1);
	}
	else
		exec_pipe(node, ms);
	return (666);
}
