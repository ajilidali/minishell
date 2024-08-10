/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:45:44 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/10 01:57:42 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	setup_redirect_out_pipe(list_commands *list, size_t i)
{
	if (list->redirections[i].flag == FD_OUT)
	{
		if (list->fd_out != STDOUT_FILENO)
			close(list->fd_out);
		list->fd_out = open(list->redirections[i].file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (list->fd_out == -1)
		{
			perror("DEDSEC");
			return (1);
		}
	}
	else if (list->redirections[i].flag == FD_ADDOUT)
	{
		if (list->fd_out != STDOUT_FILENO)
			close(list->fd_out);
		list->fd_out = open(list->redirections[i].file, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (list->fd_out == -1)
		{
			perror("DEDSEC");
			return (1);
		}
	}
	return (0);
}

void	make_here_doc_pipe(int *pipefd, list_commands *node, size_t i)
{
	int		pid;
	char	*str;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		while (1)
		{
			str = get_next_line(STDIN_FILENO);
			if ((ft_strlen(str)) > 1 && !ft_strncmp(str,
					node->redirections[i].file,
					ft_strlen(node->redirections[i].file)))
				return (free(str), close(0), get_next_line(0), exit(0));
			ft_putstr_fd(str, pipefd[1]);
			free(str);
		}
		close(pipefd[1]);
		close(pipefd[0]);
		return (free(str), close(0), get_next_line(0), exit(0));
	}
	wait(NULL);
}

static int	setup_redirect_in_pipe(list_commands *node, size_t i)
{
	int	pipefd[2];

	if (node->redirections[i].flag == FD_HD)
	{
		if (pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		make_here_doc_pipe(pipefd, node, i);
		close(pipefd[1]);
		node->fd_in = pipefd[0];
	}
	else if (node->redirections[i].flag == FD_IN)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node->fd_in = open(node->redirections[i].file, O_RDONLY);
		if (node->fd_in == -1)
		{
			perror("DEDSEC");
			return (1);
		}
	}
	return (0);
}

int	setup_redirections_pipe(list_commands *list)
{
	size_t	i;

	i = 0;
	// list->fd_in = STDIN_FILENO;
	// list->fd_out = STDOUT_FILENO;
	while (i < list->redirections_count)
	{
		if (setup_redirect_in_pipe(list, i))
			return (1);
		if (setup_redirect_out_pipe(list, i))
			return (1);
		i++;
	}
	return (0);
}

int	make_redirection_pipe(list_commands *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		node->save_in = dup(STDIN_FILENO);
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			close(node->fd_in);
			close(node->fd_out);
			return (0);
		}
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		node->save_out = dup(STDOUT_FILENO);
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			close(node->fd_in);
			close(node->fd_out);
			return (0);
		}
		close(node->fd_out);
	}
	return (1);
}

static void	exec_command(list_commands *list, MS *ms)
{
	char	*path;
	char	**envp;

	envp = get_tabenv(ms->env);
	if (!envp)
		exit(1);
	if (!list->args[0])
		exit(0);
	if (!access(list->args[0], X_OK))
		path = ft_strdup(list->args[0]);
	else
		path = find_path(list->args[0], envp);
	if (!path)
	{
		check_path(list->args[0]);
		print_errors(list->args[0], ER_CMD_NOT_FOUND);
		freetab(envp);
		exit(127);
	}
	fprintf(stderr, "\033[31;1mCMD : %s\033[m\n", list->args[0]);
	if (execve(path, list->args, envp) == -1)
	{
		free(path);
		freetab(envp);
	}
	exit(1);
}

// void	make_pipe(ASTNode *node, MS *ms)
// {
// 	int	pipefd[2];

// 	if (pipe(pipefd) == -1)
// 		return ;
// 	ms->exit_code = ft_fork_left(node->left, ms, pipefd);
// 	close(pipefd[1]);
// 	ms->exit_code = ft_fork_right(node->right, ms, pipefd);
// 	close(pipefd[0]);
// }

int	is_local_fct_pipe(MS *mini, list_commands *list)
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

void	close_node_fd_pipe(list_commands *list, int *pipefd)
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

void exec_list(list_commands *list)
{
	int pipefd[2];
	int	pid;
	int exit_code;
	int	pipe_in;

	pipe_in = -1;
	while (list)
	{
		if (list->next)
		{
			pipe(pipefd); // verif que ca marche
			list->fd_out = pipefd[1];
			if (pipe_in != -1)
				list->fd_in = pipe_in;
			else
				list->fd_in = STDIN_FILENO;
			pipe_in = pipefd[0];
		}
		else
		{
			if (pipe_in != -1)
				list->fd_in = pipe_in;
			else
				list->fd_in = STDIN_FILENO;
			list->fd_out = STDOUT_FILENO;
			pipe_in = -1;
		}
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			setup_signal_handler(0);
			exit_code = setup_redirections_pipe(list); // Fonction qui va ouvrir les fichiers relie a la commande et attribuer a fd_in et fd_out les fd des fichiers
			if (exit_code)
				exit(exit_code);
			if (!make_redirection_pipe(list)) // il va s'occuper de dup2 les fd_in et fd_out
				exit(1);
			fprintf(stderr, "fd_in = %d\nfd_out = %d\n", list->fd_in, list->fd_out);
			fprintf(stderr, "pipefd[0] = %d\npipefd[1] = %d\n", pipefd[0], pipefd[1]);
			if (list->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			exit_code = is_local_fct_pipe(give_mini(NULL, 0), list);
			if (exit_code != -1)
			{
				close_node_fd_pipe(list, pipefd);
				exit(exit_code);
			}
			exec_command(list, give_mini(NULL, 0));
		}
		else if (pid != 0)
		{
			close(pipefd[1]);
			if (!list->next)
				close(pipefd[0]);
			if (list->fd_in != STDIN_FILENO)
				close(list->fd_in);
			if (list->fd_out != STDOUT_FILENO)
				close(list->fd_out);
			wait_pids(pid, 1);
			list = list->next;
		}
	}
}

void	exec_pipe(ASTNode *node, MS *mini)
{
	// int	exit;

	// exit = 0;
	// if (!node)
	// 	return ;
	// if (node->type == AST_COMMAND)
	// {
	// 	//setup_signal_handler(0);
	// 	if (get_argc(node->args) < 1)
	// 		node->args = filter_argv(node->args, "");
	// 	exit = is_local_fct(mini, node);
	// 	if (exit != -1)
	// 	{
	// 		mini->exit_code = exit;
	// 		return (close_node_fd(node, NULL));
	// 	}
	// 	exec_command(node, mini);
	// }
	// else if (node->type == AST_PIPELINE)
	// {
	// 	make_pipe(node, mini);
	// }
	(void)mini;
	list_commands *list;
	
	list = NULL;
	copy_ast_in_list(node, &list);
	exec_list(list);
	wait_pids(0, 0);
}
