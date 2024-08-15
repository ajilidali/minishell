/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:38 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/15 13:24:16 by hclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_pwd(t_env *env)
{
	while (env)
	{
		if (ft_strncmp("PWD=", env->name_value, 4) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_oldpwd(t_env *env)
{
	while (env)
	{
		if (ft_strncmp("OLDPWD=", env->name_value, 7) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

//void	free_list(t_list *env)
//{
//	t_list	*tmp;

//	if (!env)
//		return ;
//	while (env)
//	{
//		tmp = env;
//		env = env->next;
//		ft_free(tmp->content);
//		ft_free(tmp);
//	}
//}

//t_list	*lnew_node(char *name_value)
//{
//	t_list	*node;
//	char	*folder;

//	if (!name_value)
//		return (NULL);
//	node = ft_malloc(sizeof(t_list));
//	if (!node)
//		return (NULL);
//	folder = ft_strjoin("/", name_value);
//	node->content = folder;
//	if (!node->content)
//	{
//		ft_free(node);
//		return (NULL);
//	}
//	node->next = NULL;
//	return (node);
//}

//int	add_node(char *content, t_list *list)
//{
//	if (!list)
//		return (0);
//	while (list->next)
//		list = list->next;
//	list->next = lnew_node(content);
//	if (!list->next)
//		return (0);
//	return (1);
//}

//void	delete_last_node(t_list *list)
//{
//	t_list	*temp;

//	if (!list)
//		return ;
//	temp = list;
//	while (temp->next)
//	{
//		list = temp;
//		temp = temp->next;
//	}
//	list->next = NULL;
//	ft_free(temp->content);
//	ft_free(temp);
//}
