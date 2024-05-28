/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/28 16:01:22 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_aliases(Alias *aliases)
{
    size_t i;

	i = 0;
    if (!aliases)
	{
        return -1;
	}
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
    if (strncmp(node->args[0], "alias", 5) == 0)
        exit_status = ft_alias(node->args);
    return exit_status;
}

void ft_init_ms(char **envp)
{
    size_t envp_size;
	
	envp_size = 0;
    g_ms.aliases = ft_init_alias();
    g_ms.lexer.input = NULL;
    g_ms.lexer.pos = 0;
    g_ms.lexer.length = 0;
    g_ms.alias_count = 0;
    g_ms.token.type = TOKEN_EOF;
    g_ms.token.value = NULL;
    g_ms.line = NULL;
    while (envp[envp_size])
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
    g_ms.envp[envp_size] = NULL;
}
