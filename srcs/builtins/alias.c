/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:47:01 by moajili           #+#    #+#             */
/*   Updated: 2024/06/04 09:08:51 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int alias_finder(char *cmd)
{
    size_t i = 0;

    while (i < g_ms.alias_count)
    {
        if (strcmp(g_ms.aliases[i].cmd, cmd) == 0)
            return i;
        i++;
    }
    return -1;
}

void assign_alias(char *alias, char *cmd)
{
    int replace;

    replace = alias_finder(alias);
    if (replace != -1)
    {
        g_ms.aliases[replace].cmd = strdup(alias);
        g_ms.aliases[replace].value = strdup(cmd);
        return;
    }
    printf("alias : %s\n",alias);
    g_ms.aliases[g_ms.alias_count].cmd = strdup(alias);
    g_ms.aliases[g_ms.alias_count].value = strdup(cmd);
    g_ms.alias_count++;
}

void process_arguments(int argc, char *argv[])
{
    int i = 1;

    while (i < argc)
    {
        char *arg = argv[i];
        char *equal_sign = strchr(arg, '=');
        if (equal_sign)
        {
            char *left_part = strndup(arg, equal_sign - arg);
            char *right_part = strdup(equal_sign + 1);
            trim_whitespace(left_part);
            trim_whitespace(right_part);
            if (*right_part != '\0' && *left_part != '\0')
                assign_alias(left_part,right_part);
            //printf("alias: %s not found\n",);
            free(left_part);
            free(right_part);
        } 
        i++;
    }
}

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

int run_alias(char **argv)
{
    int argc = 0;

    
    while (argv[argc])
    {
        argc++;
        printf("argv : %s\n",argv[argc]);
    }
    if (argc == 1)
        return print_aliases(g_ms.aliases);
    process_arguments(argc, argv);
    return 0;
}

