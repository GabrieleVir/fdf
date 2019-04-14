# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvirga <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 23:31:55 by gvirga            #+#    #+#              #
#    Updated: 2019/02/14 05:02:51 by gvirga           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -I ../includes -Wall -Werror -Wextra
FILES= ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putendl.c \
ft_putendl_fd.c ft_memcpy.c ft_putwchar.c ft_putwstr.c\
\
ft_memccpy.c ft_memset.c ft_bzero.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c \
ft_strcpy.c ft_strncpy.c ft_strtrim.c ft_strsplit.c \
ft_strcat.c ft_strncat.c ft_strlcat.c ft_strstr.c ft_strdup.c ft_strcpy.c \
ft_strncpy.c ft_strchri.c ft_isdigit.c ft_putnbr.c ft_putnbr_fd.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strnjoin.c \
ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
\
ft_atoi.c ft_isalpha.c ft_isalnum.c ft_ispowerof2.c\
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_itoa.c \
ft_memdel.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_itoa_base.c \
ft_lstiter.c ft_lstmap.c ft_lstcpy.c ft_wordcount.c ft_atol.c ft_push_back.c \
ft_strnboccur.c ft_strjoin_free.c ft_ipower.c ft_npower.c ft_rchr.c \
ft_nbdigit.c ft_strjoin_freei.c ft_strnew_free.c ft_strsub_free.c \
ft_strdup_free.c ft_putlstr.c ft_memljoin.c ft_llnbdigit.c ft_bigpower.c \
ft_ftoa.c ft_round_str_double.c
SRCSDIR= $(addprefix ./srcs/, $(FILES))
OBJ=$(SRCSDIR:%.c=%.o)
NAME=libft.a
LFLAGS=rc
RED=\033[0;31m
YELLOW=\033[0;33m
GREEN=\033[0;32m
END=\033[0m
VOMIS=\033[0;35m
$(VERBOSE).SILENT:

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Building <$(NAME)>$(END)"
	ar $(LFLAGS) $@ $^
	ranlib $(NAME)
	@echo "$(GREEN)SUCCESS$(END)"
.PHONY: clean
clean:
	@echo "$(RED)Suppression$(END) des fichiers objets..."
	rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	@echo "$(RED)Suppression$(END) de la $(VOMIS)<$(NAME)>$(END)..."
	/bin/rm -f $(NAME)

.PHONY: re
re: fclean all
