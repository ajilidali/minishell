/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:58:35 by moajili           #+#    #+#             */
/*   Updated: 2024/05/22 14:22:20 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/* Mandatory functions */
void	error(int err);
char	*find_path(char *cmd, char **envp);
int		get_next_line(char **line);
int     execute(char *argv, char **envp);
char	*check_local_cmd(char *cmd);

/* Bonus functions */
int		open_file(char *argv, int i);
void	usage(void);

#endif
