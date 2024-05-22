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

Alias *init_aliases(Alias **aliases)
{
    *aliases = (Alias *)malloc(sizeof(Alias) * 1);
    if (!*aliases)
        return (0);
    (*aliases)[0].cmd = NULL;
    (*aliases)[0].value = NULL;
    return (*aliases);
}

void    print_aliases(Alias *aliases)
{
    int i = 0;
    while (aliases[i].cmd)
    {
        printf("%s='%s'\n", i, aliases[i].cmd, aliases[i].value);
        i++;
    }
}