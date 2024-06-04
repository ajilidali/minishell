/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/06/04 08:22:26 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_aliases(Alias *aliases)
{
    size_t i;

	i = 0;
    if (!aliases)
        return -1;
    while (i <= g_ms.alias_count)
    {
        printf("alias %s='%s'\n", aliases[i].cmd, aliases[i].value);
        i++;
    }
    return 0;
}

int is_local_fct(ASTNode *node)
{
    size_t exit_status;

    if (!node->args[0])
        return 0;
    exit_status = 1;
    if (strcmp(node->args[0], "alias") == 0)
        exit_status = ft_alias(node->args);
    if (strcmp(node->args[0], "cd") == 0)
        exit_status = run_cd(node->args);
    if (strcmp(node->args[0], "export") == 0)
        exit_status = run_export(node->args, &g_ms.envp);
   // if (strcmp(node->args[0], "unset") == 0)
    //    exit_status = run_unset(node->args, &g_ms.env);
    
    printf("exit_status : %zu\n", exit_status);
    return exit_status;
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
