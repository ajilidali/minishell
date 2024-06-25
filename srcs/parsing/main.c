/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/25 17:24:43 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	MS	*mini;

	mini = NULL;

	mini = ft_init_ms(mini, envp); // Initialize mini
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
				sigint_handler();
				// execute_ast(mini->ast, mini);
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

	dir = getcwd(NULL, 0);
	if (!dir)
		return (NULL);
	path = ft_strjoin(dir, "$ > \033[0m");
	if (!path)
		return (free(dir), NULL);
	prompt = ft_strjoin("\033[0;32mDEDSEC ❋ ", path);
	if (!prompt)
		return (free(path), free(dir), NULL);
	return (free(path), free(dir), prompt);
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
