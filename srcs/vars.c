/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:54 by moajili           #+#    #+#             */
/*   Updated: 2024/05/24 18:28:55 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_aliases(Alias *aliases)
{
	int	i;

	i = 0;
	while (aliases[i].cmd)
	{
		printf("%s='%s'\n", aliases[i].cmd, aliases[i].value);
		i++;
	}
	return (0);
}

int	is_local_fct(void)
{
	size_t	exit_status;

	exit_status = 1;
	if (strncmp(g_ms.line, "alias", 5) == 0)
		exit_status = ft_alias();
	return (exit_status);
}

int	ft_alias(void)
{
	print_aliases(g_ms.aliases);
	return (0);
}

Alias	*ft_init_vars(void)
{
	Alias	*aliases;

	aliases = (Alias *)malloc(sizeof(Alias) * 1);
	if (!aliases)
		return (NULL);
	aliases[0].cmd = "vg";
	aliases[0].value = "valgrind --leak-check=full";
	return (aliases);
}

void	ft_init_ms(char **envp)
{
	size_t	envp_size;

	g_ms.aliases = ft_init_vars();
	g_ms.lexer.input = NULL;
	g_ms.lexer.pos = 0;
	g_ms.lexer.length = 0;
	g_ms.token.type = TOKEN_EOF;
	g_ms.token.value = NULL;
	g_ms.line = NULL;
	while (envp[envp_size])
		envp_size++;
	g_ms.envp = (char **)malloc(sizeof(char *) * (envp_size + 1));
	if (!g_ms.envp)
		return ;
	envp_size = 0;
	while (envp[envp_size])
	{
		g_ms.envp[envp_size] = strdup(envp[envp_size]);
		envp_size++;
	}
}
