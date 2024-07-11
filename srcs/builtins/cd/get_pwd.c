/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:47:03 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/11 13:47:26 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_in_list2(char **split_path, int i, t_list **list)
{
	while (split_path[i])
	{
		if (!ft_strncmp("..", split_path[i], 2))
			delete_last_node(*list);
		else if (split_path[i][0] == '.')
			;
		else
			if (!add_node(split_path[i], *list))
				return (freetab(split_path), free_list(*list), 2);
		i++;
	}
	return (freetab(split_path), 0);
}

int	split_in_list(char *path, t_list **list)
{
	char	**split_path;
	int		i;

	i = 0;
	split_path = ft_split(path, '/');
	if (!split_path)
		return (2);
	if (!*list)
	{
		if (!split_path[i])
			return (freetab(split_path), 1);
		while (split_path[i] && !ft_strncmp("..", split_path[i], 2))
			i++;
		while (split_path[i] && split_path[i][0] == '.')
			i++;
		*list = lnew_node(split_path[i++]);
		if (!*list)
			return (freetab(split_path), 2);
	}
	return (split_in_list2(split_path, i, list));
}

char	*convert_list_pwd(t_list *list)
{
	char	*pwd;
	char	*temp_pwd;

	pwd = ft_strdup("");
	temp_pwd = NULL;
	if (!pwd)
		return (free_list(list), NULL);
	while (list)
	{
		temp_pwd = ft_strjoin(pwd, (char *)list->content);
		free(pwd);
		if (!temp_pwd)
			return (free_list(list), NULL);
		pwd = temp_pwd;
		list = list->next;
	}
	return (free_list(list), pwd);
}

char	*get_pwd(char *path, char *old_pwd)
{
	t_list	*list;

	list = NULL;
	if (path[0] == '/')
	{
		if (split_in_list(path, &list))
			return (free_list(list), getcwd(NULL, 0));
		else
			return (convert_list_pwd(list));
	}
	if (split_in_list(old_pwd, &list) == 2)
		return (free_list(list), getcwd(NULL, 0));
	if (split_in_list(path, &list))
		return (free_list(list), getcwd(NULL, 0));
	return (convert_list_pwd(list));
}
