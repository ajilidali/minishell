/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:54:48 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:17:02 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_local_fct(t_ms *mini, t_astnode *node)
{
	int	exit_status;

	if (!node->args[0])
		return (0);
	exit_status = -1;
	mini->env = give_envp(NULL, 0);
	if (if_is_local(node->args[0]))
		make_redirection(node);
	if (ft_strcmp(node->args[0], "cd") == 0)
		exit_status = run_cd(node->args, mini->env);
	else if (ft_strcmp(node->args[0], "env") == 0)
		exit_status = run_env(mini->env);
	else if (ft_strcmp(node->args[0], "export") == 0)
		exit_status = run_export(node->args, &mini->env);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		exit_status = run_echo(node->args);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		exit_status = run_pwd();
	else if (ft_strcmp(node->args[0], "unset") == 0)
		exit_status = run_unset(node->args, &mini->env);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		exit_status = run_exit(node->args, mini);
	return (exit_status);
}

int	make_redirection(t_astnode *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		if (node->fd_in < 0)
			return (1);
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (ft_putendl_fd("DEDSEC : fail dup", 2), ft_exit(1), 0);
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (node->fd_out < 0)
			return (1);
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (ft_putendl_fd("DEDSEC : fail dup", 2), ft_exit(1), 0);
		close(node->fd_out);
	}
	return (1);
}

static void	exec_command(t_astnode *node, t_ms *ms)
{
	char	*path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!make_redirection(node))
		return (ft_exit(1));
	envp = get_tabenv(ms->env);
	if (!envp)
		ft_exit(1);
	if (!access(node->args[0], X_OK))
		path = ft_strdup(node->args[0]);
	else
		path = find_path(node->args[0], envp);
	if (!path)
	{
		check_path(node->args[0]);
		print_errors(node->args[0], ER_CMD_NOT_FOUND);
		freetab(envp);
		ft_exit(127);
	}
	if (execve(path, node->args, envp) == -1)
		return (ft_free(path),
			freetab(envp), check_path(path), perror("DEDSEC "), ft_exit(126));
	ft_exit(1);
}

void	restore_std(t_astnode *node, int status)
{
	if (node->fd_in != STDIN_FILENO)
	{
		if (dup2(node->save_in, STDIN_FILENO) == -1)
			return (perror("DEDSEC "), ft_exit(1));
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (dup2(node->save_out, STDOUT_FILENO) == -1)
			return (perror("DEDSEC "), ft_exit(1));
		close(node->fd_out);
	}
	close(node->save_in);
	close(node->save_out);
	give_mini(NULL, 0)->exit_code = status;
	return ;
}

void	exec_commands(t_astnode *node, t_ms *ms)
{
	int	pid;
	int	status;

	if (node->type == AST_COMMAND)
	{
		ms->exit_code = setup_redirections(node);
		if (ms->exit_code)
			return (close_node_fd(node, NULL));
		status = is_local_fct(ms, node);
		if (status != -1)
			return (restore_std(node, status));
		setup_signal_handler(2);
		pid = fork();
		if (pid == -1)
			return (ft_putendl_fd("DEDSEC : Fork fail", 3),
				ft_exit(1));
		if (pid == 0)
			exec_command(node, ms);
		waitpid(pid, &status, 0);
		if (!WTERMSIG(status))
			ms->exit_code = WEXITSTATUS(status);
		restore_std(node, ms->exit_code);
	}
	else if (node->type == AST_PIPELINE)
		exec_pipe(node);
}
