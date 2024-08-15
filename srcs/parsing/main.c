/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:59:26 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 14:19:03 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*mini;

	mini = NULL;
	mini = ft_init_ms(mini, envp);
	if (!mini)
		ft_exit(EXIT_FAILURE);
	if (getpid() != 0)
	{
		(void)argv[argc];
		while (1)
		{
			setup_signal_handler(1);
			mini->line = rl_shell(mini->line);
			mini->lexer = lexer_init(mini->line);
			mini->parser = parser_init(mini->line);
			mini->ast = parse_pipeline(&mini->parser);
			if (mini->ast)
			{
				if (check_ast_for_errors(mini->ast) != 1)
					exec_commands(mini->ast, mini);
				free_ast(mini->ast);
			}
		}
	}
	return (ft_exit(EXIT_FAILURE), 0);
}

char	*make_prompt(void)
{
	char	*prompt;
	char	*dir;
	char	*path;

	dir = env_get_var("PWD_HIDE=", give_envp(NULL, 0), true);
	if (!dir)
		dir = "";
	path = ft_strjoin(dir, "$ > \033[0m");
	if (!path)
		return (NULL);
	prompt = ft_strjoin("\033[0;32mDEDSEC ❋ ", path);
	if (!prompt)
		return (ft_free(path), NULL);
	return (ft_free(path), prompt);
}

char	*rl_shell(char *line_read)
{
	char	*prompt;

	if (line_read)
	{
		ft_free(line_read);
		line_read = NULL;
	}
	prompt = make_prompt();
	if (!prompt)
		return (clear_history(), ft_exit(EXIT_FAILURE), NULL);
	line_read = readline(prompt);
	if (line_read == NULL)
	{
		ft_free(prompt);
		clear_history();
		ft_free_gb();
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_exit(EXIT_SUCCESS);
	}
	if (line_read && *line_read)
		add_history(line_read);
	return (ft_free(prompt), line_read);
}
