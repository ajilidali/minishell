/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:09:13 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/12 00:34:38 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_backslash(char *buffer)
{
	unsigned int	i;

	i = 0;
	while (buffer[i])
	{
		if ('\n' == buffer[i])
			return (i);
		i++;
	}
	return (-1);
}

void	replace(char **buffer)
{
	int		i;
	char	*new_buffer;

	i = is_backslash(*buffer);
	new_buffer = ft_substr(*buffer, i + 1, ft_strlen(*buffer) - i);
	ft_free(*buffer);
	*buffer = new_buffer;
}

int	read_and_get(int fd, char **buffer)
{
	char	*new_str;
	char	*new_buffer;
	ssize_t	n_read;

	new_buffer = NULL;
	new_str = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!new_str)
		return (-1);
	while (*buffer && is_backslash(*buffer) == -1)
	{
		n_read = read(fd, new_str, BUFFER_SIZE);
		if (n_read == -1)
			return (ft_free(new_str), ft_free(new_buffer), -1);
		else if (n_read == 0)
			return (ft_free(new_str), 1);
		new_buffer = ft_strjoin(*buffer, new_str);
		ft_free(*buffer);
		*buffer = new_buffer;
		if (!*buffer)
			return (ft_free(new_str), -1);
		ft_bzero(new_str, BUFFER_SIZE);
	}
	return (ft_free(new_str), 0);
}

char	*get_next_line_part2(int fd, char **buffer)
{
	char	*return_line;
	int		empty;

	empty = read_and_get(fd, buffer);
	if (empty == -1)
	{
		ft_free(*buffer);
		*buffer = NULL;
		return (*buffer);
	}
	if (empty == 0)
	{
		return_line = ft_substr(*buffer, 0, is_backslash(*buffer) + 1);
		replace(buffer);
		if (!return_line && *buffer)
			return (ft_free(*buffer), *buffer = NULL, NULL);
		return (return_line);
	}
	if (!buffer || *buffer[0] == '\0')
		return_line = NULL;
	else
		return_line = ft_substr(*buffer, 0, ft_strlen(*buffer));
	ft_free(*buffer);
	*buffer = NULL;
	return (return_line);
}

/*
 * Reads a line from a file descriptor and returns it.
 * A line is a succession of characters that end with '\n'
 * or with End Of File (EOF).
 * @param fd The file descriptor to read from.
 * @return The line that has been read or NULL
 * if nothing has been read or if an error occurred.
 * The returned string should be freed when not needed anymore.
 */
char	*get_next_line(int fd)
{
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE < 0 || fd >= 1024)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer[fd])
		return (NULL);
	return (get_next_line_part2(fd, &buffer[fd]));
}
