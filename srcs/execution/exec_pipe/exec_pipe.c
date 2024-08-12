/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:45:44 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 03:31:55 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	make_pipe(int *pipefd, t_lst_cmd *node, int *pipe_in)
{
	if (node->next)
	{
		node->fd_out = pipefd[1];
		if (*pipe_in != -1)
			node->fd_in = *pipe_in;
		else
			node->fd_in = STDIN_FILENO;
		*pipe_in = pipefd[0];
	}
	else
	{
		if (*pipe_in != -1)
			node->fd_in = *pipe_in;
		else
			node->fd_in = STDIN_FILENO;
		node->fd_out = STDOUT_FILENO;
		*pipe_in = -1;
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	child_process(t_lst_cmd *node, int *pipefd)
{
	int	exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	exit_code = setup_redirections_pipe(node);
	if (exit_code)
		return (cls_fd_pipe(node, pipefd), ft_exit(exit_code));
	if (!make_redirection_pipe(node))
		return (cls_fd_pipe(node, pipefd), ft_exit(1));
	if (node->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	exit_code = is_local_fct_pipe(give_mini(NULL, 0), node);
	if (exit_code != -1)
	{
		cls_fd_pipe(node, pipefd);
		ft_exit(exit_code);
	}
	exec_command_pipe(node, give_mini(NULL, 0));
	ft_exit(EXIT_FAILURE);
}

int	parent_process(t_lst_cmd *node, int *pipefd, int pid)
{
	if (node->is_hd)
		waitpid(pid, NULL, 0);
	close(pipefd[1]);
	if (!node->next)
		close(pipefd[0]);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	if (wait_pids(pid, 1))
	{
		give_mini(NULL, 0)->exit_code = 1;
		return (1);
	}
	return (0);
}

void	exec_list(t_lst_cmd *list)
{
	int	pipefd[2];
	int	pid;
	int	pipe_in;

	pipe_in = -1;
	while (list)
	{
		if (pipe(pipefd) == -1)
			return ;
		make_pipe(pipefd, list, &pipe_in);
		pid = fork();
		if (pid == -1)
		{
			give_mini(NULL, 0)->exit_code = 1;
			return ;
		}
		if (pid == 0)
			child_process(list, pipefd);
		else if (pid != 0)
		{
			if (parent_process(list, pipefd, pid))
				return ;
			list = list->next;
		}
	}
}

void	exec_pipe(t_astnode *node)
{
	t_lst_cmd	*list;

	list = NULL;
	if (copy_ast_in_list(node, &list))
	{
		give_mini(NULL, 0)->exit_code = 1;
		return ;
	}
	setup_signal_handler(2);
	exec_list(list);
	free_cmd_list(list);
	wait_pids(0, 0);
}
