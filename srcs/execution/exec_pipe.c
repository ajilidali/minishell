/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:45:44 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/06 16:03:02 by hclaude          ###   ########.fr       */
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
		{
			mini->exit_code = exit;
			return (close_node_fd(node, NULL));
		}
		exec_command(node, mini);
	}
	else if (node->type == AST_PIPELINE)
		make_pipe(node, mini);
}
