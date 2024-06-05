# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moajili <moajili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:07:37 by moajili           #+#    #+#              #
#    Updated: 2024/06/05 17:04:42 by moajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC 		= @gcc
CFLAGS 	= -Wall -Wextra -Werror -g

SRCS	= srcs/parsing/main.c srcs/parsing/lexer.c srcs/parsing/vars.c srcs/parsing/parser.c srcs/builtins/alias.c srcs/parsing/utils.c srcs/parsing/quotes.c \
srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/pwd.c srcs/builtins/export.c srcs/builtins/unset.c srcs/builtins/env.c \
srcs/builtins/copy_env.c srcs/execution/pipex.c srcs/utils/utils.c srcs/builtins/exit.c
OBJS	= ${SRCS:.c=.o}
MAIN 	= srcs/main.c

all: ${NAME}

${NAME}: ${OBJS}
	@make -s -C ./libft
	@$(CC) ${OBJS} -Llibft -lft -lreadline -o ${NAME} ${CFLAGS}
	@echo "\033[32mminishell compiled\033[0m"

clean:
	@make clean -C ./libft
	@rm -f ${OBJS}
	@echo "\033[31mclean minishell\033[0m"

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo "Done!"

re:	fclean all

.PHONY: all clean fclean re
