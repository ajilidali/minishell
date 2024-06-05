/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:49:52 by moajili           #+#    #+#             */
/*   Updated: 2024/06/05 08:35:54 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void trim_whitespace(char *str)
{
	char *end;

	while (*str == ' ') str++;
	end = str + strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;
	*(end + 1) = '\0';
}