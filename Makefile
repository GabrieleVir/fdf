# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvirga <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 23:31:55 by gvirga            #+#    #+#              #
#    Updated: 2018/11/18 03:05:08 by gvirga           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-I./includes -Wall -Werror -Wextra
FILES= main.c 
FRAMEWORK=-framework AppKit -framework OpenGl
LDIR=lib/
LIBS=libft.a libmlx.a
OBJ=$(FILES:%.c=%.o)
NAME=libft.a
LFLAGS=rc

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(OBJ)
	ar $(LFLAGS) $@ $^
	ranlib $(NAME)
clean:
	rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
