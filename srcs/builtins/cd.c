/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:09:41 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/04 08:43:09 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     run_cd(char **command)
{
        char    *home;

        if (!command[1])
        {
        printf("tg\n");
                home = getenv("HOME");
                if (!home)
            return (printf("cd: HOME not set\n"),1);
                if (chdir(home) == -1)
                        return (printf("cd: %s: %s\n", command[1], strerror(errno)),1);
        }
        else
        {
                if (chdir(command[1]) == -1)
                        return (printf("cd: %s: %s\n", command[1], strerror(errno)),1);
        }
        return (0);
}