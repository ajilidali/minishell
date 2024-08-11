/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:23:07 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/11 20:53:26 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_command_pipe(t_lst_cmd *list, t_ms *ms)
{
	char	*path;
	char	**envp;

	envp = get_tabenv(ms->env);
	if (!envp)
		ft_exit(1);
	if (!list->args[0])
		ft_exit(0);
	if (!access(list->args[0], X_OK))
		path = ft_strdup(list->args[0]);
	else
		path = find_path(list->args[0], envp);
	if (!path)
	{
		check_path(list->args[0]);
		print_errors(list->args[0], ER_CMD_NOT_FOUND);
		freetab(envp);
		ft_exit(127);
	}
	if (execve(path, list->args, envp) == -1)
	{
		free(path);
		freetab(envp);
	}
	ft_exit(1);
}

int	is_local_fct_pipe(t_ms *mini, t_lst_cmd *list)
{
	int	exit_status;

	if (!list->args[0])
		return (0);
	exit_status = -1;
	mini->env = give_envp(NULL, 0);
	if (if_is_local(list->args[0]))
		make_redirection_pipe(list);
	if (ft_strcmp(list->args[0], "cd") == 0)
		exit_status = run_cd(list->args, mini->env);
	if (ft_strcmp(list->args[0], "env") == 0)
		exit_status = run_env(mini->env);
	if (ft_strcmp(list->args[0], "export") == 0)
		exit_status = run_export(list->args, &mini->env);
	if (ft_strcmp(list->args[0], "echo") == 0)
		exit_status = run_echo(list->args);
	if (ft_strcmp(list->args[0], "pwd") == 0)
		exit_status = run_pwd();
	if (ft_strcmp(list->args[0], "unset") == 0)
		exit_status = run_unset(list->args, &mini->env);
	if (ft_strcmp(list->args[0], "exit") == 0)
		exit_status = run_exit(list->args, mini);
	return (exit_status);
}

void	cls_fd_pipe(t_lst_cmd *list, int *pipefd)
{
	if (list->fd_in != STDIN_FILENO)
		close(list->fd_in);
	if (list->fd_out != STDOUT_FILENO)
		close(list->fd_out);
	if (pipefd)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
}
