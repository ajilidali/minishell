# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hclaude <hclaude@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/22 13:55:06 by moajili           #+#    #+#              #
#    Updated: 2024/06/05 09:31:43 by hclaude          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = @gcc
CFLAGS = -Wall -Werror -Wextra
AR=ar
ARFLAGS = rcs
NAME = libft.a
SRC_FILES = ft_atoi.c ft_strcpy.c ft_itoa.c ft_strncpy.c ft_freef.c ft_replace.c ft_isascii.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_strcmp.c ft_isalpha.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_striteri.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_split.c ft_itoa.c ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strmapi.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
ft_strndup.c ft_strcat.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJ_BONUS= $(SRC_FILES:.c=.o) $(SRC_BONUS:.c=.o)
OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ_FILES)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ_FILES)

#bonus : $(OBJ_BONUS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ_BONUS)

clean :
	@$(RM) $(OBJ_FILES)

fclean : clean
	@$(RM) $(NAME)

re: fclean all