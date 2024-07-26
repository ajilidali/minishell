/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:46:33 by moajili           #+#    #+#             */
/*   Updated: 2024/07/26 22:14:38 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	calculate_output_length(const char *in, const char *replacee,
		const char *replaced)
{
	size_t		replacee_len;
	size_t		in_len;
	size_t		replaced_len;
	size_t		count;
	const char	*tmp = in;
	size_t		final_length;

	replacee_len = ft_strlen(replacee);
	in_len = ft_strlen(in);
	replaced_len = ft_strlen(replaced);
	if (replacee_len == 0)
		return (in_len);
	count = 0;
	while ((tmp = strstr(tmp, replacee)) != NULL)
	{
		count++;
		tmp += replacee_len;
	}
	final_length = in_len + count * (replaced_len - replacee_len);
	return (final_length);
}

char	*perform_replacement(const char *in, const char *replacee,
		const char *replaced, size_t out_len)
{
	size_t	in_len;
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	in_len = ft_strlen(in);
	out = allocate_string(out_len + 1);
	while (i < in_len)
	{
		if (ft_strncmp(&in[i], replacee, ft_strlen(replacee)) == 0)
		{
			ft_strcpy(&out[j], replaced);
			i += ft_strlen(replacee);
			j += ft_strlen(replaced);
		}
		else
			out[j++] = in[i++];
	}
	return (out);
}

char	*ft_replace(char *in, const char *replacee, const char *replaced)
{
	size_t	replacee_len;
	size_t	out_len;

	if (in == NULL || replacee == NULL || replaced == NULL)
		return (NULL);
	replacee_len = ft_strlen(replacee);
	if (replacee_len == 0)
		return (ft_strdup(in));
	out_len = calculate_output_length(in, replacee, replaced);
	return (perform_replacement(in, replacee, replaced, out_len));
}
