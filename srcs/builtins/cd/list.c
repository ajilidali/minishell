/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/07/08 20:55:31 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->content);
		free(tmp);
	}
}

t_list	*lnew_node(char *name_value)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = ft_strdup(name_value);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

int	add_node(char *content, t_list *list)
{
	//t_list *temp;

	//temp = list;
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	list->next = lnew_node(content);
	if (!list->next)
		return (0);
	return (1);
}

void	delete_last_node(t_list *list)
{
	t_list *temp;

	if (!list)
		return ;
	temp = list;
	while (temp->next)
	{
		list = temp;
		temp = temp->next;
	}
	list->next = NULL;
	free(temp->content);
	free(temp);
}

// idee de la fonction : split pwd, '/'.
// Si la chaine est ".." enlever la derniere node
// si la chaine pwd est vide on laisse gerer la fonction qui s'occupe de go home
// si la chaine commence par '/' il faut juste faire un chdir si ca fonctionne on copie le pwd dans l'env
t_list	*copy_pwd(char *pwd, char *env_pwd)
{
	char	**split_pwd;
	char	**split_env_pwd;
	int		i;
	t_list	*l_pwd;

	if (!pwd)
		return (NULL); // Dans le cas ou pas d'argument mais chercher autre solution
	// Si commence par un backslash il faut juste chdir si ca marche on copie pwd dans env
	split_env_pwd = ft_split(env_pwd, '/');
	if (!split_env_pwd)
		return (NULL);
	split_pwd = ft_split(pwd, '/');
	if (!split_pwd)
		return (freetab(split_env_pwd), NULL);
	l_pwd = lnew_node(split_env_pwd[0]);
	if (!l_pwd)
		return (NULL); // faut free mais flemme
	i = 1;
	while (split_env_pwd[i])
	{
		if (ft_strncmp("..", split_env_pwd[i], 1) == 0)
		{
			delete_last_node(l_pwd);
			i++;
		}
		else
			if (!add_node(split_env_pwd[i++], l_pwd))
				return (free_list(l_pwd), NULL);
	}
	i = 0;
	while (split_pwd[i])
	{
		if (ft_strncmp("..", split_pwd[i], 1) == 0)
		{
			delete_last_node(l_pwd);
			i++;
		}
		else
			if (!add_node(split_pwd[i++], l_pwd))
				return (free_list(l_pwd), NULL);
	}
	return (l_pwd);
}
