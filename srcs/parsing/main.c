/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:59:26 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/11 13:55:20 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	MS	*mini;

	mini = NULL;
	mini = ft_init_ms(mini, envp);
	sigint_handler();
	if (getpid() != 0)
	{
		(void)argc;
		(void)argv;
		while ((mini->line = rl_shell(mini->line)))
		{
			mini->lexer = lexer_init(mini->line);
			mini->parser = parser_init(mini->line);
			mini->ast = parse_pipeline(&mini->parser);
			if (mini->ast)
			{
				exec_commands(mini->ast, mini);
				free_ast(mini->ast);
			}
		}
	}
	return (0);
}

char	*make_prompt(void)
{
	char	*prompt;
	char	*dir;
	char	*path;

	dir = env_get_var("PWD", give_envp(NULL, 0));
	if (!dir)
		return (NULL);
	path = ft_strjoin(dir, "$ > \033[0m");
	if (!path)
		return (NULL);
	prompt = ft_strjoin("\033[0;32mDEDSEC ❋ ", path);
	if (!prompt)
		return (free(path), NULL);
	return (free(path), prompt);
}

char	*rl_shell(char *line_read)
{
	char	*prompt;

	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	prompt = make_prompt();
	if (!prompt)
		return (NULL);
	line_read = readline(prompt);
	if (line_read == NULL)
	{
		free(prompt);
		clear_history();
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	// LA FONCTION EXIT EST FAITE MAIS
	// TROUVER UN MOYEN DE FREE line_read
	// '/!\'

	//if (ft_strcmp(line_read, "exit") == 0)
	//{
	//	rl_clear_history();
	//	free(line_read);
	//	exit(127);
	//}
	if (line_read && *line_read)
		add_history(line_read);
	return (free(prompt), line_read);
}
