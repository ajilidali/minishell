/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:21:04 by moajili           #+#    #+#             */
/*   Updated: 2023/10/31 13:40:59 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_taille(long int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (!n)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			size;
	long int	aux;
	char		*nbr;

	aux = n;
	size = ft_taille(aux);
	nbr = (char *)malloc((size + 1) * sizeof(char));
	if (!(nbr))
		return (NULL);
	nbr[--size + 1] = '\0';
	if (aux < 0)
		aux = -aux;
	while (size >= 0)
	{
		nbr[size--] = (aux % 10) + '0';
		aux = aux / 10;
	}
	if (nbr[0] == '0' && nbr[1])
		nbr[0] = '-';
	return (nbr);
}
