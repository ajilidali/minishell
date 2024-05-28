# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moajili <moajili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:07:37 by moajili           #+#    #+#              #
#    Updated: 2024/05/28 15:51:10 by moajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g3

#SRCS	= pipex/pipex_bonus.c pipex/utils.c pipex/utils_bonus.c srcs/main.c srcs/lexer.c srcs/vars.c srcs/parser.c srcs/pipex.c
SRCS	= srcs/main.c srcs/lexer.c srcs/vars.c srcs/parser.c srcs/pipex.c srcs/Exec/alias.c srcs/utils.c
OBJS	= ${SRCS:.c=.o}
MAIN 	= srcs/main.c

all: ${NAME}

${NAME}: ${OBJS}
					@make re -C ./libft
					@$(CC) ${OBJS} -Llibft -lft -lreadline -o ${NAME} ${CFLAGS} -g3 -fsanitize=address
					@echo "Done!"

clean:
					@make clean -C ./libft
					@rm -f ${OBJS}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(NAME)
					@echo "Done!"

re:			fclean all

.PHONY: all clean fclean re
