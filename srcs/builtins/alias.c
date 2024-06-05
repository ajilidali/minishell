/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:47:01 by moajili           #+#    #+#             */
/*   Updated: 2024/06/04 17:21:44 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int alias_finder(Alias *aliases,char *cmd, int alias_count)
{
    int i = 0;

    while (i < alias_count)
    {
        if (strcmp(aliases[i].cmd, cmd) == 0)
            return i;
        i++;
    }
    return -1;
}

void assign_alias(MS *mini, char *alias, char *cmd)
{
    int replace;

    replace = alias_finder(mini->aliases, alias, mini->alias_count);
    if (replace != -1)
    {
        mini->aliases[replace].cmd = strdup(alias);
        mini->aliases[replace].value = strdup(cmd);
        return;
    }
    mini->aliases[mini->alias_count].cmd = strdup(alias);
    mini->aliases[mini->alias_count].value = strdup(cmd);
    mini->alias_count++;
}

void process_arguments(MS *mini,int argc)
{
    int i = 1;

    while (i < argc)
    {
        char *arg = mini->ast->args[i];
        char *equal_sign = strchr(arg, '=');
        if (equal_sign)
        {
            char *left_part = strndup(arg, equal_sign - arg);
            char *right_part = strdup(equal_sign + 1);
            trim_whitespace(left_part);
            trim_whitespace(right_part);
            if (*right_part != '\0' && *left_part != '\0')
                assign_alias(mini,left_part,right_part);
            free(left_part);
            free(right_part);
        } 
        i++;
    }
}

int print_aliases(Alias *aliases, int alias_count)
{
    int i;

	i = 0;
    if (!aliases)
        return -1;
    while (i <= alias_count)
    {
        if (aliases[i].cmd)
            printf("alias %s='%s'\n", aliases[i].cmd, aliases[i].value);
        i++;
    }
    return 0;
}

int run_alias(MS *mini, ASTNode *node)
{
    int argc = 0;
    
    if (!node)
        return 1;
    while (node->args[argc])
        argc++;
    if (argc == 1)
        return print_aliases(mini->aliases, mini->alias_count);
    process_arguments(mini,argc);
    return 0;
}

