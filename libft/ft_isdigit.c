/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:44:10 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 22:10:38 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Checks if the passed character is a digit.
 * @param a The character to check.
 * @return Returns 1 if the character is a digit (0-9), 0 otherwise.
 */
int	ft_isdigit(int a)
{
	return ((a >= 48 && a <= 57));
}

int	ft_strnum(char *str)
{
	int		i;
	size_t	num;

	if (!str)
		return (0);
	i = 0;
	num = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num++;
		i++;
	}
	if (num == ft_strlen(str))
		return (1);
	return (0);
}
