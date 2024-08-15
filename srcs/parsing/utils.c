/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:47:32 by moajili           #+#    #+#             */
/*   Updated: 2024/08/14 21:58:19 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	char_counter(const char *str, char c)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(str) - 1;
	while (len >= 0)
		if (str[len--] == c)
			count++;
	return (count);
}

int	is_all_spaces(const char *str)
{
	int	i;

	if (str[0] == '\0')
	{
		return (1);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*extract_variable(char *in, size_t *end_pos)
{
	size_t	start;
	size_t	i;
	char	*variable;

	i = 0;
	if (!in || char_counter(in, '$') == 0)
		return (NULL);
	while (in[i] && in[i] != '$')
		i++;
	start = i;
	if (i < ft_strlen(in) && in[i] == '$')
	{
		if (in[i + 1] == ' ' || in[i + 1] == '\0')
			return (NULL);
		i++;
		while (i < ft_strlen(in) && (in[i] == '?' || in[i] == '_'
				|| ft_isalnum(in[i])))
			i++;
	}
	else
		return (NULL);
	variable = allocate_string((i - start) + 1);
	ft_strncpy(variable, &in[start], i - start);
	*end_pos = i;
	return (variable);
}

char	*replace_variables(char *in)
{
	char	*variable;
	char	*final;
	size_t	end_pos;

	if (!in)
		return (NULL);
	variable = extract_variable(in, &end_pos);
	if (!variable)
		return (in);
	final = ft_replace(in, variable, parse_variable(variable));
	if (char_counter(final, '$') != 0)
		final = replace_variables(final);
	return (ft_free(variable), final);
}

char	*ext_val(const char *input, size_t start, size_t len)
{
	char	*value;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	value = allocate_string(len + 1);
	if (!value)
		return (NULL);
	while (i < len)
	{
		if (input[start + i] != '\'' && input[start + i] != '\"')
			value[j++] = input[start + i];
		i++;
	}
	return (value);
}
