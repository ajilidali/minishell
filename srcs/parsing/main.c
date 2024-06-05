/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:50:54 by moajili           #+#    #+#             */
/*   Updated: 2024/06/05 08:35:37 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	MS	*mini;

	mini = NULL;
	mini = ft_init_ms(mini, envp); // Initialize mini
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
				execute_ast(mini);
				free_ast(mini->ast);
			}
		}
	}
	return (0);
}


void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
}

char	*rl_shell(char *line_read)
{
	char *dir;
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	dir = ft_strjoin("\033[0;32mDEDSEC ❋ ", ft_strjoin(getcwd(NULL, 0), "$ > \033[0m"));
	line_read = readline(dir);
	if (line_read == NULL)
	{
		rl_clear_history();
		exit(0);
	}
	if (ft_strcmp(line_read, "exit") == 0)
	{
		rl_clear_history();
		free(line_read);
		exit(0);
	}
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
