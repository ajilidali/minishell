/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:46:33 by moajili           #+#    #+#             */
/*   Updated: 2024/06/05 10:17:16 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	calculate_output_length(const char *in, const char *replacee,
		const char *replaced)
{
	size_t	replacee_len;
	size_t	replaced_len;
	size_t	out_len;
	size_t	i;

	replacee_len = ft_strlen(replacee);
	replaced_len = ft_strlen(replaced);
	out_len = ft_strlen(in);
	if (replacee_len == 0)
		return (out_len);
	i = 0;
	while (i <= ft_strlen(in) - replacee_len)
	{
		if (ft_strncmp(&in[i], replacee, replacee_len) == 0)
		{
			out_len = out_len - replacee_len + replaced_len;
			i += replacee_len;
		}
		else
			i++;
	}
	return (out_len);
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
	out = malloc(out_len + 1);
	if (out == NULL)
		return (NULL);
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
	out[out_len] = '\0';
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
