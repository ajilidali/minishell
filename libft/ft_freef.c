/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freef.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 11:58:09 by ajordan-          #+#    #+#             */
/*   Updated: 2024/04/25 15:47:33 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

void	ft_splitf(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
}

void	ft_joinf(char *join)
{
	if (join)
		free(join);
}

void	ft_type(va_list args, const char format)
{
	if (format == 's')
		ft_splitf(va_arg(args, char **));
	else if (format == 'p')
		ft_joinf(va_arg(args, char *));
	// else if (format == 'p')
	//		ft_print_ptr(va_arg(args, unsigned long long));
	//	else if (format == 'd' || format == 'i')
	//	ft_putnbr(va_arg(args, int));
	//	else if (format == 'u')
	//		ft_uprint(va_arg(args, unsigned int));
	// else if (format == 'x' || format == 'X')
	//		ft_print_hex(va_arg(args, unsigned int), format);
	//	else if (format == '%')
	//		ft_percent();
}

void	ft_freef(const char *format, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_type(args, format[i + 1]);
			i++;
		}
		i++;
	}
	va_end(args);
}
