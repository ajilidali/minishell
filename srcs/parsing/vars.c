/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/06/04 09:19:29 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int is_local_fct(ASTNode *node)
{
    size_t exit_status;

    if (!node->args[0])
        return 0;
    exit_status = 1;
    if (strcmp(node->args[0], "alias") == 0)
        exit_status = run_alias(node->args);
    if (strcmp(node->args[0], "cd") == 0)
        exit_status = run_cd(node->args);
    if (strcmp(node->args[0], "env") == 0)
        exit_status = run_env(g_ms.envp);
    if (strcmp(node->args[0], "export") == 0)
        exit_status = run_export(node->args, &g_ms.envp);
    if (strcmp(node->args[0], "echo") == 0)
        exit_status = run_echo(node->args);   
    if (strcmp(node->args[0], "pwd") == 0)
        exit_status = run_pwd();
    if (strcmp(node->args[0], "unset") == 0)
        exit_status = run_unset(node->args, &g_ms.envp);
   // if (strcmp(node->args[0], "unset") == 0)
    //    exit_status = run_unset(node->args, &g_ms.env);
    
    printf("exit_status : %zu\n", exit_status);
    return exit_status;
}

Alias* ft_init_alias(void)
{
    size_t i = 0;
    Alias *aliases = (Alias *)malloc(sizeof(Alias) * 1024);
    if (!aliases)
    {
        fprintf(stderr, "Memory allocation error\n");
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

void ft_init_ms(char **envp)
{
    /*size_t envp_size;
	
	envp_size = 0;*/
    g_ms.aliases = ft_init_alias();
    g_ms.lexer.input = NULL;
    g_ms.lexer.pos = 0;
    g_ms.lexer.length = 0;
    g_ms.alias_count = 0;
    g_ms.token.type = TOKEN_EOF;
    g_ms.token.value = NULL;
    g_ms.line = NULL;
    g_ms.envp = copy_env(envp);
   /* while (envp[envp_size])
        envp_size++;
    g_ms.envp = (char **)malloc(sizeof(char *) * (envp_size + 1));
    if (!g_ms.envp)
        return;
    envp_size = 0;
    while (envp[envp_size])
    {
        g_ms.envp[envp_size] = strdup(envp[envp_size]);
        envp_size++;
    }
    g_ms.envp[envp_size] = NULL;*/
}
