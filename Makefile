# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:07:37 by moajili           #+#    #+#              #
#    Updated: 2024/07/11 13:47:42 by hclaude          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC 		= @cc
INCLUDE = -I./includes
CFLAGS 	= -Wall -Wextra -Werror -g3

OBJDIR= .objs

SRCS	= srcs/parsing/main.c srcs/parsing/lexer.c srcs/parsing/vars.c srcs/parsing/parser.c srcs/builtins/alias.c srcs/parsing/utils.c srcs/parsing/quotes.c \
srcs/builtins/echo.c srcs/builtins/cd/cd.c srcs/builtins/pwd.c srcs/builtins/export.c srcs/builtins/unset.c srcs/builtins/env.c \
srcs/utils/utils.c srcs/builtins/exit.c srcs/execution/redirect.c srcs/parsing/parsecmd.c \
srcs/utils/copy_env.c srcs/parsing/args.c srcs/execution/exec.c srcs/execution/exec_utils.c \
srcs/utils/signals.c srcs/utils/utils2.c srcs/builtins/cd/cd2.c srcs/execution/exec_pipe.c srcs/utils/print_errors.c srcs/builtins/cd/list.c srcs/builtins/cd/get_pwd.c \

OBJS	= $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

all: ${NAME}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

${NAME}: ${OBJS}
	@make -s -C ./libft
	@$(CC) ${OBJS} -Llibft -lft $(INCLUDE) -lreadline -ltermcap -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -o ${NAME} ${CFLAGS}
	@echo "\033[32mminishell compiled\033[0m"

clean:
	@make -s clean -C ./libft
	@rm -rf $(OBJDIR)
	@echo "\033[31mclean minishell\033[0m"

fclean: clean
	@make -s fclean -C ./libft
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
