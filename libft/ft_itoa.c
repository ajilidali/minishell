/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:56:11 by hclaude           #+#    #+#             */
/*   Updated: 2024/06/03 18:12:11 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countdigit(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

static void	recustr(long int n, char *str, int count)
{
	if (count != -1)
	{
		if (n <= 9 && n >= 0)
			str[count] = '0' + n;
		else
		{
			recustr(n % 10, str, count--);
			recustr(n / 10, str, count--);
		}
	}
}

/*
 * Converts an integer into a string.
 * @param n The integer to convert.
 * @return A new string representing the integer.
 * If the function fails, it returns NULL.
 */
char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			count;
	long int	num;

	i = 0;
	num = n;
	count = countdigit(num);
	str = ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[i] = '-';
		num = num * -1;
	}
	recustr(num, str, count - 1);
	return (str);
}
