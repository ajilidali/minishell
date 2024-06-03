# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:07:37 by moajili           #+#    #+#              #
#    Updated: 2024/06/03 18:06:56 by hclaude          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC 		= @gcc
CFLAGS 	= -Wall -Wextra -Werror -g3

#SRCS	= pipex/pipex_bonus.c pipex/utils.c pipex/utils_bonus.c srcs/main.c srcs/lexer.c srcs/vars.c srcs/parser.c srcs/pipex.c
SRCS	= srcs/parsing/main.c srcs/parsing/lexer.c srcs/parsing/vars.c srcs/parsing/parser.c srcs/execution/alias.c srcs/parsing/utils.c srcs/parsing/quotes.c \
srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/pwd.c srcs/builtins/export.c srcs/builtins/unset.c srcs/builtins/env.c \
srcs/builtins/copy_env.c srcs/execution/pipex.c srcs/utils/utils.c
OBJS	= ${SRCS:.c=.o}
MAIN 	= srcs/main.c

all: ${NAME}

${NAME}: ${OBJS}
	make -C ./libft
	@$(CC) ${OBJS} -Llibft -lft -lreadline -o ${NAME} ${CFLAGS} -g3
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
