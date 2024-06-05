/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/06/04 18:35:11 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int is_local_fct(MS *mini, ASTNode *node) //here
{
  size_t	exit_status;

  if (!node->args[0])
        return 0;
    exit_status = 1;
    if (strcmp(node->args[0], "alias") == 0)
        exit_status = run_alias(mini, node);
    if (strcmp(node->args[0], "cd") == 0)
        exit_status = run_cd(node->args, mini->envp);
    if (strcmp(node->args[0], "env") == 0)
        exit_status = run_env(mini->envp);
    if (strcmp(node->args[0], "export") == 0)
        exit_status = run_export(node->args, &mini->envp);
    if (strcmp(node->args[0], "echo") == 0)
        exit_status = run_echo(node->args);   
    if (strcmp(node->args[0], "pwd") == 0)
        exit_status = run_pwd();
    if (strcmp(node->args[0], "unset") == 0)
        exit_status = run_unset(node->args, &mini->envp);
    if (ft_strcmp(node->args[0], "exit") == 0)
		    run_exit(node->args);
    
    printf("\nexit_status : %zu\n", exit_status);
    return (exit_status);
}

Alias	*ft_init_alias(void)
{
	size_t	i;
	Alias	*aliases;

	i = 0;
	aliases = (Alias *)malloc(sizeof(Alias) * 1024);
	if (!aliases)
	{
		ft_putendl_fd("Memory allocation error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (i < 1024)
	{
		aliases[i].cmd = NULL;
		aliases[i].value = NULL;
		i++;
	}
	return (aliases);
}

MS	*ft_init_ms(MS *mini, char **envp)
{
	mini = malloc(sizeof(MS));
	if (mini == NULL)
		return (NULL);
	mini->aliases = ft_init_alias();
	mini->lexer.input = NULL;
	mini->lexer.pos = 0;
	mini->lexer.length = 0;
	mini->token.type = TOKEN_EOF;
	mini->token.value = NULL;
	mini->envp = copy_env(envp);
	mini->parser.lexer = mini->lexer;
	mini->parser.current_token = mini->token;
	mini->ast = NULL;
	mini->line = NULL;
	mini->alias_count = 0;
	return (mini);
}
