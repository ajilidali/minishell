/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/22 17:35:51 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_aliases(Alias *aliases)
{
    int i = 0;
    while (aliases[i].cmd)
    {
        printf("%s='%s'\n", aliases[i].cmd, aliases[i].value);
        i++;
    }
}

void is_local_fct(void)
{
    if (strncmp(g_ms.line, "alias",5) == 0)
        ft_alias();
}

void ft_alias(void)
{
    print_aliases(g_ms.aliases);
}

Alias *ft_init_vars(void)
{
    Alias *aliases = (Alias *)malloc(sizeof(Alias) * 1);
    if (!aliases)
        return NULL;
    aliases[0].cmd = "vg";
    aliases[0].value = "valgrind --leak-check=full";
    return aliases;
}

void ft_new_alias(void)
{
    
}


void ft_init_ms(void)
{
    g_ms.aliases = ft_init_vars();
    g_ms.lexer.input = NULL;
    g_ms.lexer.pos = 0;
    g_ms.lexer.length = 0;
    g_ms.token.type = TOKEN_EOF;
    g_ms.token.value = NULL;
    g_ms.line = NULL;
}
